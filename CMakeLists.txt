cmake_minimum_required(VERSION 3.31)
project(GcodeEM_0)

set(CMAKE_CXX_STANDARD 20)

add_executable(GcodeEM_0 Source/main.cpp
        Source/Parser.cpp
        Source/Parser.h)
