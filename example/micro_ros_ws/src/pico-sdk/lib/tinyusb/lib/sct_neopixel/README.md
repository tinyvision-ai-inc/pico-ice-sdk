# sct_neopixel
SCT based NeoPixel driver

This library uses the State Configurable Timer (SCTimer or SCT) found in several NXP microcontrollers including the LPC55 to drive multiple strings of NeoPixels.

## Theory of operation

This driver uses the states to encode the bit that is being output. 