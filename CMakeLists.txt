cmake_minimum_required(VERSION 3.10)
project(closure C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

include_directories(deps)
include(deps/panic/panic.cmake)
include(deps/error/error.cmake)
include(deps/option/option.cmake)
include(deps/result/result.cmake)
include(deps/alligator/alligator.cmake)

add_library(closure sources/closure.h sources/closure.c)
target_link_libraries(closure PRIVATE alligator)
target_link_libraries(closure PUBLIC option result)

add_library(adder examples/adder.h examples/adder.c)
target_include_directories(adder PRIVATE sources)
target_link_libraries(adder PUBLIC closure)

add_executable(adder-main examples/adder-main.c)
target_link_libraries(adder-main PRIVATE adder)
