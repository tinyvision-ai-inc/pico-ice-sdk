/*
 * MIT License
 *
 * Copyright (c) 2023 tinyVision.ai
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// libc
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

// pico-ice-sdk
#include "boards/pico_ice.h"
#include "ice_wishbone.h"
#include "ice_spi.h"

// Parse input data from a serial link (such as CDC uart) and control
// an SPI peripheral to query the FPGA registers and send an answer back.
// https://wishbone-utils.readthedocs.io/en/latest/wishbone-tool/#serial-bridge
// https://github.com/litex-hub/wishbone-utils/blob/master/wishbone-tool/crates/bridge/src/bridges/uart.rs
// There is an extra non-standard ACK byte at the end of the WRITE command.
void ice_wishbone_serial(uint8_t byte) {
    static enum {
        FPGA_GET_COMMAND,
        FPGA_GET_LENGTH,
        FPGA_GET_ADDR_0,
        FPGA_GET_ADDR_1,
        FPGA_GET_ADDR_2,
        FPGA_GET_ADDR_3,
        FPGA_GET_VALUE,
    } state = FPGA_GET_COMMAND;
    static enum {
        FPGA_COMMAND_WRITE = 0x00,
        FPGA_COMMAND_READ = 0x01,
    } cmd;
    static uint32_t addr;
    static uint8_t data_size = 0;
    static uint8_t data[0xFF];
    static uint8_t data_pos;

    switch (state) {
    case FPGA_GET_COMMAND:
        if (cmd == FPGA_COMMAND_READ || cmd == FPGA_COMMAND_WRITE) {
            cmd = byte;
            state++;
        }
        break;
    case FPGA_GET_LENGTH:
        data_size = byte;
        data_pos = 0;
        addr = 0;
        state++;
        break;
    case FPGA_GET_ADDR_0:
    case FPGA_GET_ADDR_1:
    case FPGA_GET_ADDR_2:
    case FPGA_GET_ADDR_3:
        addr = (addr << 8) | byte;
        state++;
        break;
    case FPGA_GET_VALUE:
        if (cmd == FPGA_COMMAND_WRITE) {
            data[data_pos++] = byte;
            data_size;
            if (data_pos == data_size) {
                ice_wishbone_serial_write_cb(addr, data, data_size);
                ice_wishbone_serial_tx_cb(FPGA_COMMAND_WRITE);
                state = FPGA_GET_COMMAND;
            }
        }
        break;
    }
    if (state == FPGA_GET_VALUE && cmd == FPGA_COMMAND_READ) {
        ice_wishbone_serial_read_cb(addr, data, data_size);
        for (uint8_t i = 0; i < data_size; i++) {
            ice_wishbone_serial_tx_cb(data[i]);
        }
        state = FPGA_GET_COMMAND;
    }
}

// https://github.com/xobs/spibone

// Read protocol:
//     Write: 01 | AA | AA | AA | AA
//     [Wishbone Operation]
//     Read:  01 | VV | VV | VV | VV
void ice_wishbone_spi_read(uint32_t addr, uint8_t *data, size_t data_size) {
    uint8_t header[5] = {
        0x01,
        (addr >> 24) & 0xFF,
        (addr >> 16) & 0xFF,
        (addr >> 8) & 0xFF,
        (addr >> 0) & 0xFF,
    };
    uint8_t byte;

    ice_spi_chip_select(ICE_FPGA_CSN_PIN);
    ice_spi_write_blocking(header, sizeof header);
    while (ice_spi_read_blocking(&byte, 1), byte == 0xFF);
    assert(byte == 0x01);
    ice_spi_read_blocking(data, data_size);
    ice_spi_chip_deselect(ICE_FPGA_CSN_PIN);
}

// Write protocol:
//     Write: 00 | AA | AA | AA | AA | VV | VV | VV | VV
//     [Wishbone Operation]
//     Read:  00
void ice_wishbone_spi_write(uint32_t addr, const uint8_t *data, size_t data_size) {
    uint8_t header[5] = {
        0x00,
        (addr >> 24) & 0xFF,
        (addr >> 16) & 0xFF,
        (addr >> 8) & 0xFF,
        (addr >> 0) & 0xFF,
    };
    uint8_t byte;

    ice_spi_chip_select(ICE_FPGA_CSN_PIN);
    ice_spi_write_blocking(header, sizeof header);
    ice_spi_write_blocking(data, data_size);
    while (ice_spi_read_blocking(&byte, 1), byte == 0xFF);
    ice_spi_chip_deselect(ICE_FPGA_CSN_PIN);
    assert(byte == 0x00);
}
