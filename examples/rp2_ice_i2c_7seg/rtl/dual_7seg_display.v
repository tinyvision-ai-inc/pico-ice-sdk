// 7-segment display Pmod controller
// This is a controller for the 7-seg display module as provided by 1bitsquared:
// https://1bitsquared.com/products/pmod-7-segment-display

`default_nettype none
`timescale 10us/100ns

module dual_7seg_display (
  input  wire clk,
  input  wire rst_n,

  // 7-segment pins
  output wire[6:0] seg_pins_o,
  output wire seg_select_o,

  // Hex digit input
  input  wire[3:0] hex0_data_i,
  input  wire[3:0] hex1_data_i
);
  reg[7:0] counter_q, counter_d;
  reg[3:0] hex_data;
  reg[6:0] seg_pins;
  wire seg_select;

  assign seg_select = counter_q[7];
  assign seg_select_o = seg_select;
  assign seg_pins_o = seg_pins;

  always @(*) begin
    case (hex_data)
      4'h0: seg_pins = 7'b0000001;
      4'h1: seg_pins = 7'b1001111;
      4'h2: seg_pins = 7'b0010010;
      4'h3: seg_pins = 7'b0000110;
      4'h4: seg_pins = 7'b1001100;
      4'h5: seg_pins = 7'b0100100;
      4'h6: seg_pins = 7'b0100000;
      4'h7: seg_pins = 7'b0001111;
      4'h8: seg_pins = 7'b0000000;
      4'h9: seg_pins = 7'b0000100;
      4'hA: seg_pins = 7'b0001000;
      4'hB: seg_pins = 7'b1100000;
      4'hC: seg_pins = 7'b0110001;
      4'hD: seg_pins = 7'b1000010;
      4'hE: seg_pins = 7'b0110000;
      4'hF: seg_pins = 7'b0111000;
    endcase
  end

  always @(posedge clk) begin
    // Registers definition
    counter_q <= rst_n ? counter_d : 0;
  end
  always @(*) begin
    // Combinational logic
    counter_d = counter_q + 1;

    if (seg_select) begin
      hex_data = hex0_data_i;
    end else begin
      hex_data = hex1_data_i;
    end
  end

endmodule
