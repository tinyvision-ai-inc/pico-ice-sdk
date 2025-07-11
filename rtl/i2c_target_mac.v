// I2C target low-level MAC module

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
  parameter I2C_TX_SDA_RESET = 1;

  // Sense the positive and negative edges of SCL
  wire i2c_posedge;
  wire i2c_negedge;

  // Delay lines to sense the edges, as well as prevent an accidental start/stop
  // condition in case the SCL line is a bit late (still high) while SDA goes down.
  // Also removes potential metastability on these input signals.
  reg i2c_scl_q, i2c_scl_qq, i2c_scl_qqq;
  reg i2c_sda_q, i2c_sda_qq, i2c_sda_qqq;

  // Persistent bit setting SDA during one SCL cycle
  reg i2c_tx_sda_q, i2c_tx_sda_d;

  // Next value to be queued into i2c_tx_sda_d for transmission
  reg i2c_tx_next_q, i2c_tx_next_d;

  assign i2c_posedge = !i2c_scl_qqq & i2c_scl_qq;
  assign i2c_negedge = i2c_scl_qqq & !i2c_scl_qq;
  assign i2c_rx_bit_valid_o = i2c_posedge;
  assign i2c_bus_start_o = i2c_scl_q && i2c_scl_i && i2c_sda_qqq && !i2c_sda_qq;
  assign i2c_bus_stop_o = i2c_scl_q && i2c_scl_i && !i2c_sda_qqq && i2c_sda_qq;
  assign i2c_rx_bit_valid_o = i2c_posedge;
  assign i2c_rx_bit_valid_o = i2c_posedge;
  assign i2c_rx_bit_data_o = i2c_sda_i;

  // Whenever i2c_tx_sda_q is LOW, short SDA to ground by enabling the output
  // with value 0. Otherwise, disable the output to let the pull-up drive the pin high.
  assign i2c_sda_o = 0;
  assign i2c_sda_oe = !i2c_tx_sda_q;

  always @(posedge clk) begin
    // Registers definition
    i2c_scl_q <= rst_n ? i2c_scl_i : 0;
    i2c_scl_qq <= rst_n ? i2c_scl_q : 0;
    i2c_scl_qqq <= rst_n ? i2c_scl_qq : 0;
    i2c_sda_q <= rst_n ? i2c_sda_i : 0;
    i2c_sda_qq <= rst_n ? i2c_sda_q : 0;
    i2c_sda_qqq <= rst_n ? i2c_sda_qq : 0;
    i2c_tx_sda_q <= rst_n ? i2c_tx_sda_d : I2C_TX_SDA_RESET;
    i2c_tx_next_q <= rst_n ? i2c_tx_next_d : I2C_TX_SDA_RESET;
  end
  always @(*) begin
    // Combinational logic
    i2c_tx_next_d = i2c_tx_next_q;
    i2c_tx_sda_d = i2c_tx_sda_q;

    if (i2c_tx_bit_valid_i) begin
      i2c_tx_next_d = i2c_tx_bit_data_i;
    end

    if (i2c_negedge) begin
      i2c_tx_sda_d = i2c_tx_next_q;
      i2c_tx_next_d = I2C_TX_SDA_RESET;
    end

    if (i2c_bus_start_o || i2c_bus_stop_o) begin
      i2c_tx_sda_d = I2C_TX_SDA_RESET;
      i2c_tx_next_d = I2C_TX_SDA_RESET;
    end
  end

endmodule
