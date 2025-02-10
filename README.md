# pico-ice-sdk

[Doc](http://pico-ice.tinyvision.ai/)
| [Hardware](https://github.com/tinyvision-ai-inc/pico-ice)
| [SDK](https://github.com/tinyvision-ai-inc/pico-ice-sdk)
| [Schematic](https://raw.githubusercontent.com/tinyvision-ai-inc/pico-ice/main/Board/Rev3/pico-ice.pdf)
| [Assembly](https://htmlpreview.github.io/?https://github.com/tinyvision-ai-inc/pico-ice/blob/main/Board/Rev3/bom/ibom.html)
| [Discord](https://discord.gg/t2CzbAYeD2)

This is the SDK for building custom firmware for the RP2040 on the [pico-ice](https://pico-ice.tinyvision.ai/) board and RP2350 on [pico2-ice](https://pico2-ice.tinyvision.ai/) board.

### To quickly get started:
Provided you have the compilers setup.
For riscv, you may add `-DPICO_GCC_TRIPLE=riscv64-unknown-elf` to the cmake command if your 'riscv64' compiler supports rp2350/rv32.

- clone the repository
- run `git submodules update --init`
- got into the folder of the example you wish to try
- `mkdir build && cd build`
- `cmake -DPICO_BOARD=pico_ice ..` or `cmake -DPICO_BOARD=pico2_ice ..` or `cmake -DPICO_BOARD=pico2_ice -DPICO_PLATFORM=rp2350-riscv ..`
- `make -j8`
- Copy the generated uf2 to the board after setting it to flashing mode
