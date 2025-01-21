cmake_minimum_required(VERSION 3.29)
project(Poker_Face_C_)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Poker_Face_C_ "Poker Face.cpp" AIPlayer.cpp UserPlayer.cpp GameRunner.cpp)
