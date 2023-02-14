# pico_flash_tool

It will offer a REPL accessible over the USB-UART #0 with commands for
interacting with the flash chip for debugging purposes:

## `0x00000000`

Writing a hexadecimal address in this format sets the current address.

### `w 00 00 00 00 [...] 00`

Program memory at the current address with content `00 00 00 00 [...] 00`.
The address must be a multiple of 256 (0x100).
The content must containt 256 bytes.

### `r`

Read memory page at the current address and print it as hexadecimal such as `00 00 00 00 [...] 00`.

### `e`

Erase memory page at the current address which will set it to `FF FF FF FF [...] FF`.

### `z`

Fill memory page at the current address with zeroes, which will set it to `00 00 00 00 [...] 00`.

### `w`

Issue a wake-up command to the flash.

### `i`

Run the complete `flash_init()` function.
