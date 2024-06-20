
module top (
  input CLK,
  output LED_R,
  output LED_G,
  output LED_B,
);

  localparam N = 22;

  reg [N:0] counter;

  always @(posedge CLK) begin
    counter <= counter + 1;
  end

  assign LED_R = 1'b1;
  assign LED_G = counter[N];
  assign LED_B = 1'b1;

endmodule
