// I2C target

`default_nettype none
`timescale 10us/100ns

module i2c_target #(
  // Shifted I2C representation, not masked:
  // represents the address after removing the R/W bit
  parameter I2C_TARGET_ADDR = 7'h66
) (
  input  wire clk,
  input  wire rst_n,

  // I2C pins
  input  wire i2c_scl_i,
  input  wire i2c_sda_i,
  output wire i2c_sda_o,
  output wire i2c_sda_oe,

  // I2C RX
  output wire[7:0] i2c_rx_byte_data_o,
  output wire i2c_rx_byte_valid_o,

  // I2C TX
  input  wire[7:0] i2c_tx_byte_data_i,
  input  wire i2c_tx_byte_valid_i,

  // I2C transaction
  output wire i2c_transaction_start_o,
  output wire i2c_transaction_stop_o
);
  // I2C bus state machine
  parameter I2C_STATE_INIT = 0;
  parameter I2C_STATE_TX_DATA = 1;
  parameter I2C_STATE_RX_DATA = 2;
  parameter I2C_STATE_WAIT_ACK = 3;
  parameter I2C_STATE_ADDR_MATCH = 4;
  parameter I2C_STATE_SKIP = 5;
  reg[2:0] i2c_state_q, i2c_state_d;
  reg[2:0] i2c_next_state_q, i2c_next_state_d;

  // I2C bit-level I/O
  reg i2c_tx_bit_data;
  reg i2c_tx_bit_valid;
  reg[$clog2(8)+1:0] i2c_rx_bit_counter_d, i2c_rx_bit_counter_q;
  wire i2c_rx_bit_data;
  wire i2c_rx_bit_valid;
  reg i2c_rx_ack_d, i2c_rx_ack_q;

  // I2C byte-level I/O
  reg[7:0] i2c_rx_byte_data_d, i2c_rx_byte_data_q;
  reg i2c_rx_byte_valid_d, i2c_rx_byte_valid_q;
  wire[6:0] i2c_address;
  wire i2c_rw_flag;

  // I2C start/stop condition
  wire i2c_bus_start;
  wire i2c_bus_stop;

  // I2C transaction state
  reg i2c_transaction_start;
  reg i2c_transaction_stop;

  // Low-level I2C MAC that converts the raw signal to bits and events
  i2c_target_mac i2c_target_mac_inst (
    .clk(clk),
    .rst_n(rst_n),

    .i2c_sda_i(i2c_sda_i),
    .i2c_sda_o(i2c_sda_o),
    .i2c_sda_oe(i2c_sda_oe),
    .i2c_scl_i(i2c_scl_i),

    .i2c_rx_bit_data_o(i2c_rx_bit_data),
    .i2c_rx_bit_valid_o(i2c_rx_bit_valid),

    .i2c_tx_bit_data_i(i2c_tx_bit_data),
    .i2c_tx_bit_valid_i(i2c_tx_bit_valid),

    .i2c_bus_start_o(i2c_bus_start),
    .i2c_bus_stop_o(i2c_bus_stop)
  );

  assign i2c_transaction_stop_o = i2c_bus_stop;
  assign i2c_address = i2c_rx_byte_data_q[7:1];
  assign i2c_rw_flag = i2c_rx_byte_data_q[0];
  assign i2c_rx_byte_data_o = i2c_rx_byte_data_q;
  assign i2c_rx_byte_valid_o = i2c_rx_byte_valid_q;

  always @(posedge clk) begin
    // Registers definition
    i2c_state_q <= rst_n ? i2c_state_d : 0;
    i2c_next_state_q <= rst_n ? i2c_next_state_d : 0;
    i2c_rx_byte_valid_q <= rst_n ? i2c_rx_byte_valid_d : 0;
    i2c_rx_byte_data_q <= rst_n ? i2c_rx_byte_data_d : 0;
    i2c_rx_bit_counter_q <= rst_n ? i2c_rx_bit_counter_d : 0;
    i2c_rx_ack_q <= rst_n ? i2c_rx_ack_d : 0;
  end
  always @(*) begin
    // Combinational logic
    i2c_state_d = i2c_state_q;
    i2c_transaction_start = 0;
    i2c_rx_byte_valid_d = 0;
    i2c_rx_byte_data_d = i2c_rx_byte_data_q;
    i2c_rx_bit_counter_d = i2c_rx_bit_counter_q;
    i2c_next_state_d = i2c_next_state_q;
    i2c_tx_bit_data = 1;
    i2c_tx_bit_valid = 0;

    case (i2c_state_q)

      I2C_STATE_INIT: begin
        i2c_state_d = I2C_STATE_RX_DATA;
        i2c_next_state_d = I2C_STATE_ADDR_MATCH;
      end

      I2C_STATE_RX_DATA: begin
        if (i2c_rx_bit_valid) begin
          // Shift in one more bit
          i2c_rx_byte_data_d = {i2c_rx_byte_data_q[6:0], i2c_rx_bit_data};

          if (i2c_rx_bit_counter_q == 7) begin
            // Reaching the end: as soon as the incoming bit is stored,
            // trigger the byte ready signal and reset the counter
            i2c_rx_bit_counter_d = 0;

            // The captured byte is only transmitted after the address is updated
            i2c_rx_byte_valid_d = (i2c_next_state_d != I2C_STATE_ADDR_MATCH);

            i2c_state_d = i2c_next_state_q;
          end else begin
            i2c_rx_bit_counter_d = i2c_rx_bit_counter_q + 1;
          end
        end
      end

      I2C_STATE_TX_DATA: begin
        if (i2c_rx_bit_valid) begin
          i2c_tx_bit_valid = 0;
        end
      end

      I2C_STATE_ADDR_MATCH: begin
        if (i2c_address == I2C_TARGET_ADDR) begin
          i2c_transaction_start = 1;
          i2c_state_d = I2C_STATE_WAIT_ACK;
          i2c_tx_bit_data = 0;
          i2c_tx_bit_valid = 1;

          if (i2c_rx_byte_data_q[0]) begin
            i2c_next_state_d = I2C_STATE_TX_DATA;
          end else begin
            i2c_next_state_d = I2C_STATE_RX_DATA;
          end

        end else begin
          i2c_state_d = I2C_STATE_SKIP;
        end
      end

      I2C_STATE_WAIT_ACK: begin
        if (i2c_rx_bit_valid) begin
          i2c_state_d = i2c_next_state_q;
        end
      end

      I2C_STATE_SKIP: begin
        // Do nothing, wait that an event resets the state
      end

    endcase

    // In case a stop condition is detected, reset the state unconditionally
    if (i2c_bus_start || i2c_bus_stop) begin
      i2c_state_d = I2C_STATE_INIT;
      i2c_rx_bit_counter_d = 0;
    end
  end

endmodule
