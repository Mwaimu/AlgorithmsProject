cmake_minimum_required(VERSION 3.6)
project(Algorithms)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp main.h Edge.cpp Edge.h Network.cpp Network.h Node.cpp Node.h)
add_executable(lockThing ${SOURCE_FILES})