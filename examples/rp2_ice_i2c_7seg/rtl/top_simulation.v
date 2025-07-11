// Top-level module for simulation (iverilog)

`timescale 1us / 100ns
`default_nettype none

module top;
  reg clk;
  reg rst_n;

  wire i2c_sda_o;
  wire i2c_sda_oe;
  wire i2c_sda_i;
  wire i2c_scl_i;

  wire[6:0] seg_pins;
  wire seg_select;

  wire i2c_sda = i2c_sda_oe ? i2c_sda_o : i2c_sda_i;

  // Poor man's test bench: record an I2C transaction and insert it in simulation
`define DATA_SIZE 36
  reg[`DATA_SIZE-1:0] i2c_sda_data = 'b11111110_11_11_00_00_11_11_00_00_11_0_011111111;
  reg[`DATA_SIZE-1:0] i2c_scl_data = 'b11111111_01_01_01_01_01_01_01_01_01_0_111111111;

  assign i2c_sda_i = i2c_sda_data[`DATA_SIZE-1];
  assign i2c_scl_i = i2c_scl_data[`DATA_SIZE-1];

  always begin
    // Shift the test input data out once every clock cycles
    i2c_sda_data = {i2c_sda_data[`DATA_SIZE-2:0], i2c_sda_data[`DATA_SIZE-1]};
    i2c_scl_data = {i2c_scl_data[`DATA_SIZE-2:0], i2c_scl_data[`DATA_SIZE-1]};

    for (integer i = 0; i < 4 * 2; i = i + 1) begin
      #5 clk = ~clk;
    end
  end

  main main (
    .clk(clk),
    .rst_n(rst_n),

    .i2c_sda_i(i2c_sda_i),
    .i2c_sda_o(i2c_sda_o),
    .i2c_sda_oe(i2c_sda_oe),
    .i2c_scl_i(i2c_scl_i),

    .seg_pins_o(seg_pins),
    .seg_select_o(seg_select)
  );

  initial begin

    $dumpfile("top_simulation.vcd");
    $dumpvars(0, top);

    clk = 0;
    rst_n = 0;

    #10
    rst_n = 1;

    #10000
    $finish();

  end

endmodule
