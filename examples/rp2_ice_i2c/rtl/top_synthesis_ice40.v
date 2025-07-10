// Top-level module for synthesis (iCE40)

`timescale 1ns / 1ps
`default_nettype none

`define PIN_OUTPUT_TRISTATE_PIN_INPUT 6'b1010_01

module top (
  // Input system clock exported the RP2350
  input wire CLK,

  // Communication with the RP2350
  input wire DEFAULT_I2C_SDA,
  input wire DEFAULT_I2C_SCL,

  // Debug output
  output wire ICE_PMOD_A_TOP_IO1,
  output wire ICE_PMOD_A_TOP_IO2,
  output wire ICE_PMOD_A_TOP_IO3,
  output wire ICE_PMOD_A_TOP_IO4,
  output wire ICE_PMOD_A_BOT_IO1,
  output wire ICE_PMOD_A_BOT_IO2,
  output wire ICE_PMOD_A_BOT_IO3,
  output wire ICE_PMOD_A_BOT_IO4
);

  // I2C bus
  wire i2c_scl_di = DEFAULT_I2C_SCL;
  wire i2c_sda_oe;
  wire i2c_sda_do;
  wire i2c_sda_di;

  // Reset logic
  reg[7:0] rst_counter;
  wire rst_n;

  // Bi-directional pin support for I2C SDA
  SB_IO #(
    .PIN_TYPE(`PIN_OUTPUT_TRISTATE_PIN_INPUT),
    .PULLUP(1'b0)
  ) i2c_io (
    .PACKAGE_PIN(DEFAULT_I2C_SDA),
    .OUTPUT_ENABLE(i2c_sda_oe),
    .D_OUT_0(i2c_sda_do),
    .D_IN_0(i2c_sda_di)
  );

  // Reset signal leveraging all registers set to 0 on startup
  always @(posedge CLK) begin
    rst_counter = rst_counter[7] ? rst_counter : rst_counter + 1;
  end
  assign rst_n = rst_counter[7];

  // Main module

  main #() main (
    .clk(CLK),
    .rst_n(rst_n),

    // I2C
    .i2c_sda_i(i2c_sda_di), .i2c_sda_o(i2c_sda_do), .i2c_sda_oe(i2c_sda_oe),
    .i2c_scl_i(i2c_scl_di),

    // Debug pinout that matches the FX2LA plugged directly to a Pmod.
    // Note that with most logic analyzers, shift by one row to avoid a short-circuit
    // Easy to verify by feeding a counter into the debug port and sorting the signals.
    .debug_o({
      ICE_PMOD_A_TOP_IO4, ICE_PMOD_A_BOT_IO4, ICE_PMOD_A_TOP_IO3, ICE_PMOD_A_BOT_IO3,
      ICE_PMOD_A_TOP_IO2, ICE_PMOD_A_BOT_IO2, ICE_PMOD_A_TOP_IO1, ICE_PMOD_A_BOT_IO1
    })
  );

endmodule
