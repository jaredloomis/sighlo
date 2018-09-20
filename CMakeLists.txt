cmake_minimum_required (VERSION 3.10)
project(database)

# Search the directory tree, put files into `sources` variable
file(GLOB_RECURSE sources src/*.cpp src/*.h)

add_executable(database ${sources})
target_compile_options(database PUBLIC -std=c++17 -Wall -fmax-errors=1)
target_include_directories(database PUBLIC src)
