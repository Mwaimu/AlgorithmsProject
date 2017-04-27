cmake_minimum_required(VERSION 3.6)
project(Algorithms)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Edge.cpp Edge.h Node.cpp Node.h Network.cpp Network.h main.cpp main.h)
add_executable(lockThing ${SOURCE_FILES})