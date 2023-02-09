Project template
================
This example content is meant to be copied to create your own project.

Once it is copied, and execute a shel inside this directory:

```sh
# add the dependencies as submodules
git submodule add https://github.com/tinyvision-ai-inc/pico-ice-sdk
git submodule add https://github.com/raspberrypi/pico-sdk
git -C pico-sdk submodule update --recursive
```

You can then build your own project as a normal CMake project:

```
mkdir -p build
cd build
cmake ..
make
```

This should produce a `firmware.uf2` file to flash onto the pico-ice RP2040 chip.

See [doc](https://pico-ice.tinyvision.ai/) for where to go next.
