cmake_minimum_required(VERSION 3.12)
project(uf2tools)

add_executable(bin2uf2 bin2uf2.c libuf2.c)
add_executable(uf22bin uf22bin.c libuf2.c)
add_executable(uf2dump uf2dump.c libuf2.c)
