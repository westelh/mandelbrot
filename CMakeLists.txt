cmake_minimum_required(VERSION 3.10)
project(mandelbrot CXX)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_compile_options(
        $<$<CONFIG:DEBUG>:-O0>
        $<$<CONFIG:DEBUG>:-g3>
        $<$<CONFIG:RELEASE>:-O3>
        $<$<CONFIG:RELEASE>:-mtune=native>
        $<$<CONFIG:RELEASE>:-march=native>)
add_link_options(-lpthread)
add_compile_definitions($<$<CONFIG:RELEASE>:NDEBUG>)

add_executable(a.out main.cpp mandelbrot.cpp bmp.cpp)
target_link_libraries(a.out PRIVATE Threads::Threads)

add_subdirectory(gui)
