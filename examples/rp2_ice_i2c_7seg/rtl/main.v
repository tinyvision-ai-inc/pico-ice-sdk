// Main file of the project.
// Instanciate all blocks used by the project.
// Glue logic to tie them together.

`default_nettype none
`timescale 10us/100ns

module main (
  input clk,
  input rst_n,

  // I2C pins
  input wire i2c_scl_i,
  input wire i2c_sda_i,
  output wire i2c_sda_o,
  output wire i2c_sda_oe,

  // 7-segment pins
  output wire[6:0] seg_pins_o,
  output wire seg_select_o
);
  // RX data endpoint
  wire[7:0] i2c_rx_byte_data;
  wire i2c_rx_byte_valid;

  // TX data endpoint
  wire[7:0] i2c_tx_byte_data;
  wire i2c_tx_byte_valid = 0;

  // Storage for the received byte
  reg[7:0] i2c_rx_byte_d, i2c_rx_byte_q;

  // Instance of an I2C target controller.
  // It will receive data from the I2C controller and pulse every time
  // a byte was read or written, so that we can use it in the design.
  i2c_target #(
    .I2C_TARGET_ADDR('h66)
  ) i2c_target_inst (
    .clk(clk),
    .rst_n(rst_n),

    .i2c_sda_i(i2c_sda_i),
    .i2c_sda_o(i2c_sda_o),
    .i2c_sda_oe(i2c_sda_oe),
    .i2c_scl_i(i2c_scl_i),

    .i2c_rx_byte_data_o(i2c_rx_byte_data),
    .i2c_rx_byte_valid_o(i2c_rx_byte_valid),

    .i2c_tx_byte_data_i(i2c_tx_byte_data),
    .i2c_tx_byte_valid_i(i2c_tx_byte_valid)
  );

  dual_7seg_display dual_7seg_display_inst (
    .clk(clk),
    .rst_n(rst_n),

    .seg_pins_o(seg_pins_o),
    .seg_select_o(seg_select_o),

    .hex0_data_i(i2c_rx_byte_q[3:0]),
    .hex1_data_i(i2c_rx_byte_q[7:4])
  );

  // Capture bytes from I2C
  always @(posedge clk) begin
    // Register definition
    i2c_rx_byte_q <= rst_n ? i2c_rx_byte_d : 0;
  end
  always @(*) begin
    // Combinational logic
    i2c_rx_byte_d = i2c_rx_byte_q;

    if (i2c_rx_byte_valid) begin
      i2c_rx_byte_d = i2c_rx_byte_data;
    end
  end

endmodule
