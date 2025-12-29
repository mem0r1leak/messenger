cmake_minimum_required(VERSION 3.16)
project(messenger)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(core)
add_subdirectory(crypto)
add_subdirectory(tests)
