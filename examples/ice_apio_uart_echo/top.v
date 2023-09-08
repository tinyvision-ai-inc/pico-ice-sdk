module top (
    input CLK,
    input UART_RX,
    output UART_TX
);
    assign UART_TX = UART_RX;
endmodule
