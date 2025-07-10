// I2C target receiver module

`default_nettype none
`timescale 10us/100ns

module i2c_target_mac (
  input  wire clk,
  input  wire rst_n,

  // I2C pins
  input  wire i2c_scl_i,
  input  wire i2c_sda_i,
  output wire i2c_sda_o,
  output wire i2c_sda_oe,

  // I2C bus I/O
  output wire i2c_rx_bit_data_o,
  output wire i2c_rx_bit_valid_o,
  input  wire i2c_tx_bit_data_i,
  input  wire i2c_tx_bit_valid_i,

  // I2C bus state
  output wire i2c_bus_start_o,
  output wire i2c_bus_stop_o
);
  parameter I2C_SDA_RESET = 1;

  // Delay lines to wait that the signals stabilize for one extra clock
  reg i2c_negedge_q, i2c_negedge_d;
  reg i2c_posedge_q, i2c_posedge_d;

  // Delay lines to sense the edges
  reg i2c_scl_q;
  reg i2c_sda_q;

  // Persistent bit setting SDA during one SCL cycle
  reg i2c_tx_sda_q, i2c_tx_sda_d;

  // Next value to be queued into i2c_tx_sda_d for transmission
  reg i2c_tx_next_q, i2c_tx_next_d;

  assign i2c_rx_bit_valid_o = i2c_posedge_q;
  assign i2c_bus_start_o = i2c_scl_q && i2c_scl_i && i2c_sda_q && !i2c_sda_i;
  assign i2c_bus_stop_o = i2c_scl_q && i2c_scl_i && !i2c_sda_q && i2c_sda_i;
  assign i2c_rx_bit_valid_o = i2c_posedge_q;
  assign i2c_rx_bit_valid_o = i2c_posedge_q;
  assign i2c_rx_bit_data_o = i2c_sda_i;
  assign i2c_sda_o = 0;
  assign i2c_sda_oe = !i2c_tx_sda_q;

  always @(posedge clk) begin
    // Registers definition
    i2c_negedge_q <= rst_n ? i2c_negedge_d : 0;
    i2c_posedge_q <= rst_n ? i2c_posedge_d : 0;
    i2c_scl_q <= rst_n ? i2c_scl_i : 0;
    i2c_sda_q <= rst_n ? i2c_sda_i : 0;
    i2c_tx_sda_q <= rst_n ? i2c_tx_sda_d : I2C_SDA_RESET;
    i2c_tx_next_q <= rst_n ? i2c_tx_next_d : I2C_SDA_RESET;
  end
  always @(*) begin
    // Combinational logic
    i2c_posedge_d = i2c_scl_i && !i2c_scl_q;
    i2c_negedge_d = !i2c_scl_i && i2c_scl_q;
    i2c_tx_next_d = i2c_tx_next_q;
    i2c_tx_sda_d = i2c_tx_sda_q;

    if (i2c_tx_bit_valid_i) begin
      i2c_tx_next_d = i2c_tx_bit_data_i;
    end

    if (i2c_negedge_q) begin
      i2c_tx_sda_d = i2c_tx_next_q;
      i2c_tx_next_d = I2C_SDA_RESET;
    end

    if (i2c_bus_start_o || i2c_bus_stop_o) begin
      i2c_tx_sda_d = I2C_SDA_RESET;
      i2c_tx_next_d = I2C_SDA_RESET;
    end
  end

endmodule
