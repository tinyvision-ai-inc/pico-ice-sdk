These examples can be built in-place as a CMake project:

```
cd pico_example_dir
mkdir -p build
cd build
cmake ..
make
```

This should produce a `.uf2` file to flash onto the pico-ice RP2040 chip.
See the [documentation](https://pico-ice.tinyvision.ai/) for how to do this.
