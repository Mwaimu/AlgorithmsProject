cmake_minimum_required(VERSION 3.6)
project(Algorithms)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Algorithm.cpp Algorithm.h Sensor.cpp Sensor.h)
add_executable(lockThing ${SOURCE_FILES})