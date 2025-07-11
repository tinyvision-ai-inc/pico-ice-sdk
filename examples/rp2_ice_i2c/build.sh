# Sample script to show how to build and load the demo into a pico2-ice
cmake -B build -DPICO_BOARD=pico2_ice
cmake --build build
picotool load -f build/rp2_ice_blinky.uf2
picotool reboot
