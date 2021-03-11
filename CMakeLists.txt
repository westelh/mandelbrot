cmake_minimum_required(VERSION 3.10)
project(mandelbrot CXX)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-pthread
        $<$<CONFIG:DEBUG>:-O0>
        $<$<CONFIG:DEBUG>:-g3>
        $<$<CONFIG:RELEASE>:-O3>
        $<$<CONFIG:RELEASE>:-mtune=native>
        $<$<CONFIG:RELEASE>:-march=native>)
add_compile_definitions($<$<CONFIG:RELEASE>:NDEBUG>)

add_executable(a.out main.cpp mandelbrot.cpp bmp.cpp)

add_subdirectory(gui)
