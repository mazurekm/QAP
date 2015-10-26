cmake_minimum_required (VERSION 2.8)
project(Strategy)

add_library(${PROJECT_NAME} Strategy.cpp)

add_subdirectory(unittests)