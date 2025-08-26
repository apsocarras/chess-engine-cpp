cmake_minimum_required(VERSION 3.12)
project(ChessEngineTutorial VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
    bit_manips 
    bit_manips.cpp 
    bit_manips.hpp
    bbc_types.hpp
    )

add_executable(bbc bbc.cpp)
target_link_libraries(bbc PUBLIC bit_manips)
