`timescale 1ns / 1ps
`default_nettype none

module testbench;
    logic clk, rst;
    logic [2:0] cnt_d;

    top uut (
        .clk_i(clk),
        .rst_ni(rst),
        .cnt_o(cnt_d)
    );


    always begin
         #5 clk = ~clk;
    end

    initial begin
        $dumpfile("iverilog.vcd");
        $dumpvars(0, testbench);

        clk = 0;
        rst = 0;

        #10
        rst = 1;

        #10000
        $finish();
    end

endmodule
