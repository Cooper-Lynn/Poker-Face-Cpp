cmake_minimum_required(VERSION 3.29)
project(Poker_Face_C_)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Poker_Face_C_
        Cards.cpp
        Cards.hpp
    "Poker Face.cpp")
