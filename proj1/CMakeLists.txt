cmake_minimum_required(VERSION 3.6)
project(proj1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Algorithms.cpp Algorithms.h Sensor.cpp Sensor.h Point.cpp Point.h)
add_executable(project1 ${SOURCE_FILES})