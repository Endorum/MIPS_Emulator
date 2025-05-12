cmake_minimum_required(VERSION 3.28)
project(MIPS_Emulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(MIPS_Emulator main.cpp
        include/CPU.hpp
        src/CPU.cpp
        include/Memory.hpp)
