`timescale 1ns / 1ps
`default_nettype none

module ice40 (
    input clk,
    output led_red,
    output led_green,
    output led_blue
);

    top top0 (
        .clk_i(clk),
        .rst_ni(1),
        .cnt_o({ led_red, led_green, led_blue }),
    );

endmodule
