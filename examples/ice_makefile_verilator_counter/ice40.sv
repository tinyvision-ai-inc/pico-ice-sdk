module gateware (
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
