cmake_minimum_required(VERSION 3.16)
project(faz2Project C)

set(CMAKE_C_STANDARD 99)

add_executable(faz2Project main.c cJSON.c cJSON.h)

target_link_libraries(faz2Project ws2_32)