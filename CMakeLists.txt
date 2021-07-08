cmake_minimum_required(VERSION 3.19)
project(cesar_hack C)

set(CMAKE_C_STANDARD 99)

set(HEADER ./header)
set(SRC ./src)

include_directories(${HEADER})
include_directories(${SRC})


add_executable(cesar_hack src/main.c header/cesar_function.h)