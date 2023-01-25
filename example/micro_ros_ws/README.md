This example is a seperate ROS2 workspace created with reference to this guide

https://robofoundry.medium.com/raspberry-pi-pico-ros2-via-micro-ros-actually-working-in-1-hr-9f7a3782d3e3

A modification was made in micro_ros_ws/src/micro_ros_raspberrypi_pico_sdk/CMakeLists.txt to add a 1 second delay after the Pico connects to a computer to prevent communication errors

Modification under "# Configure Pico" of "add_compile_definitions(PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS=1000)"

Tested with ROS2 Galactic

The current buildfile generated is for micro_ros_ws/src/micro_ros_raspberrypi_pico_sdk/pico_micro_ros_example.c
