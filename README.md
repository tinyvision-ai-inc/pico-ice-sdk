# pico-ice-sdk

[Doc](http://pico-ice.tinyvision.ai/)
| [Hardware](https://github.com/tinyvision-ai-inc/pico-ice)
| [SDK](https://github.com/tinyvision-ai-inc/pico-ice-sdk)
| [Schematic](https://raw.githubusercontent.com/tinyvision-ai-inc/pico-ice/main/Board/Rev3/pico-ice.pdf)
| [Assembly](https://htmlpreview.github.io/?https://github.com/tinyvision-ai-inc/pico-ice/blob/main/Board/Rev3/bom/ibom.html)
| [Discord](https://discord.gg/t2CzbAYeD2)

This is the SDK for building custom firmware for the RP2040 on the [pico-ice](https://pico-ice.tinyvision.ai/) board.
Part of this SDK runs on the RP2040 on the Pico-Ice circuit board, it is used to build the pico-ice firmware. Part runs on your desktop, and communicates with the pico-ice over a USB cable. 

## Installation

First clone this repository. 

`git clone https://github.com/tinyvision-ai-inc/pico-ice-sdk`

Then install the two libraries it requires. 

```
cd pico-ice-sdk
git submodule update --init
```
