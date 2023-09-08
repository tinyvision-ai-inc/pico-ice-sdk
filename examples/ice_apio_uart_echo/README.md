# ice_apio_uart_echo

This example makes use of the [apio](https://apiodoc.readthedocs.io/) command line build system for [oss-cad-suite](https://github.com/YosysHQ/oss-cad-suite-build).

Build with `apio build` and deploy with `apio upload`.
See the [doc](https://pico-ice.tinyvision.ai/using_apio.html) for more.

It makes use of the default firmware's USB UART forwarding feature:

1. Connect the board to the host with an USB cable
2. Connect to the USB-UART interface of the [default firmware](https://pico-ice.tinyvision.ai/getting_started.html#default-firmware).
3. In the terminal window that opens, only when this example is loaded, everything typed in should be echoed back.

It is possible to verify if it worked by loading the RGB blink example: with it, nothing should be echoed back.
