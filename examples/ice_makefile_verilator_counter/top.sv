`default_nettype none

module top (
    input  clk_i,
    input  rst_ni,

    // output the counter's value
    output [2:0] cnt_o
);
    logic [20:0] cnt_q;

    always_ff @(posedge clk_i) begin
        if (rst_ni) begin
            cnt_q <= cnt_q + 1;
        end else begin
            cnt_q <= 0;
        end
    end

    assign cnt_o = cnt_q[20:18];

endmodule
