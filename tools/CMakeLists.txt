cmake_minimum_required(VERSION 3.12)
project(uf2tools)

include_directories(uf2dump ${CMAKE_CURRENT_LIST_DIR}/../include)

add_executable(bin2uf2 bin2uf2.c libuf2.c)
add_executable(uf22bin uf22bin.c libuf2.c)
add_executable(uf2dump uf2dump.c libuf2.c)

install(TARGETS bin2uf2 uf22bin uf2dump)
