cmake_minimum_required(VERSION 3.13)
project(hash_table)

set(CMAKE_CXX_STANDARD 17)

add_executable(hash_table
        main.cpp
        lib/HashMap.hpp
        lib/util.cpp
        lib/util.h)

add_executable(test
        lib/HashMap.hpp
        lib/util.cpp
        lib/util.h
        test.cpp)