/* Blink the RGB LED */

module top (
  input clock,
  output LED_R,
  output LED_G,
  output LED_B
);
  reg [31:0] counter=0;

  always@(posedge clock) begin
    counter <= counter +1;
  end

  assign {LED_R,LED_G,LED_B} = counter[28:26];

endmodule
