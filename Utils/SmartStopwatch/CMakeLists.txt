cmake_minimum_required (VERSION 2.8)
project(SmartStopwatch)

add_library(${PROJECT_NAME} SmartStopwatch.cpp)

add_subdirectory(unittests)
