#include <ctype.h>
#include <stdio.h>

#include "boards/pico_ice.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"

#include "ice/flash.h"
#include "ice/sdk.h"
#include "ice/usb.h"

int repl_last_char;
bool repl_last_held;

static int repl_getchar(void)
{
    int c;

    if (repl_last_held) {
        repl_last_held = false;
        return repl_last_char;
    }

    // busy-wait with a slow delay: this is for interactive I/O, no need to be fast
    while ((c = getchar_timeout_us(10000)) == PICO_ERROR_TIMEOUT)
        // call tud_task() since we are blocking, similar to preemptive multitasking
        tud_task();
    if (c == '\r' || c == '\n')
        printf("\r\n");
    else
        putchar(c);
    return c;
}

static void repl_ungetchar(int c)
{
    assert(!repl_last_held);
    repl_last_char = c;
    repl_last_held = true;
}

static inline void memdump(uint8_t const *buf, size_t sz)
{
    for (size_t i = 0; i < sz; i++) {
        printf(" %02X", buf[i]);
        if (i % 0x20 == (0x20 - 1))
            printf("\n");
    }
    printf("\n");
}

static inline bool repl_parse_error(char *msg, char c)
{
    // reset whatever was being input
    repl_last_held = false;

    printf("\nerror: expected %s got '%c'\n", msg, c);
    return false;
}

static bool repl_expect(char *str)
{
    for (char *s = str; *s != '\0'; s++)
        if (repl_getchar() != *s)
            return repl_parse_error(str, *s);
    return true;
}

static bool xdigit(uint8_t *nibble, int c)
{
    // if we could read a hex digit, append it
    if (c >= '0' && c <= '9') {
        *nibble = c - '0';
        return true;
    }
    if (c >= 'A' && c <= 'F') {
        *nibble = 10 + c - 'A';
        return true;
    }
    if (c >= 'a' && c <= 'f') {
        *nibble = 10 + c - 'a';
        return true;
    }

    // if not a hex digit, put it back onto the stream and stop here
    repl_ungetchar(c);
    return false;
}

static inline bool repl_parse_u32(uint32_t *u32)
{
    bool read_anything = false;
    int c;

    *u32 = 0;
    for (uint8_t u; xdigit(&u, c = repl_getchar()); *u32 = *u32 << 4 | u)
        read_anything = true;

    if (!read_anything)
            return repl_parse_error("hex digit", c);

    // At least one hex digit read, valid input
    return true;
}

static inline bool repl_parse_address(uint32_t *addr)
{
    if (!repl_expect("0x"))
        return false;
    return repl_parse_u32(addr);
}

static bool repl_parse_newline(void)
{
    int c;

    switch (c = repl_getchar()) {
    case '\r':
    case '\n':
    case EOF:
        return true;
    default:
        repl_ungetchar(c);
        return repl_parse_error("newline", c);
    }
}

static void repl_command_write(void)
{
    uint8_t buf[ICE_FLASH_PAGE_SIZE] = {0};
    uint32_t addr;

    if (!repl_expect(" ") || !repl_parse_address(&addr) || !repl_parse_newline())
        return;

    ice_flash_program_page(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN, addr, buf);
    printf("%s 0x%08X done\r\n", __func__, addr);
}

static void repl_command_read(void)
{
    uint32_t addr;
    uint8_t buf[ICE_FLASH_PAGE_SIZE] = {0};

    if (!repl_expect(" ") || !repl_parse_address(&addr) || !repl_parse_newline())
        return;

    ice_flash_read(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN, addr, buf, sizeof buf);
    printf("%s 0x%08X done\r\n", __func__, addr);
    memdump(buf, sizeof buf);
}

static void repl_command_erase(void)
{
    uint32_t addr;

    if (!repl_expect(" ") || !repl_parse_address(&addr) || !repl_parse_newline())
        return;

    ice_flash_erase_sector(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN, addr);
    printf("%s 0x%08X done\r\n", __func__, addr);
}

static void repl_command_zero(void)
{
    uint8_t buf[ICE_FLASH_PAGE_SIZE] = {0};
    uint32_t addr;

    if (!repl_expect(" ") || !repl_parse_address(&addr) || !repl_parse_newline())
        return;

    ice_flash_program_page(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN, addr, buf);
    printf("%s 0x%08X done\r\n", __func__, addr);
}

static void repl_command_sleep(void)
{
    if (!repl_parse_newline())
        return;

    ice_flash_sleep(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN);
    printf("%s done\r\n", __func__);
}

static void repl_command_wakeup(void)
{
    if (!repl_parse_newline())
        return;

    ice_flash_wakeup(spi_fpga_flash, ICE_FLASH_SPI_CSN_PIN);
    printf("%s done\r\n", __func__);
}

static void repl_command_init(void)
{
    if (!repl_parse_newline())
        return;

    ice_flash_init();
    printf("%s done\r\n", __func__);
}

int main(void)
{
    // Let the FPGA boot up from flash
    ice_sdk_init();

    // Enable USB-UART #0 output
    stdio_init_all();

    for (;;) {
        tud_task();

        printf("pico-flash-tool> ");

        switch (repl_getchar()) {
        case 'w':
            repl_command_write();
            break;
        case 'r':
            repl_command_read();
            break;
        case 'e':
            repl_command_erase();
            break;
        case 'z':
            repl_command_zero();
            break;
        case 's':
            repl_command_sleep();
            break;
        case 'u':
            repl_command_wakeup();
            break;
        case 'i':
            repl_command_init();
            break;
        case '\r':
        case '\n':
            break;
        default:
            printf("\navailable commands: w r e z s u i\n");
            break;
        }
    }

    return 0;
}
