module top (
    input clk,
    output led_blue,
    output led_green,
    output led_red
);
    localparam N = 24;

    reg [N-1:0] counter;

    always @(posedge clk) begin
        counter <= counter + 1;
    end

    assign led_green = counter[N - 1];
    assign led_blue = counter[N - 2];
    assign led_red = counter[N - 3];
endmodule
