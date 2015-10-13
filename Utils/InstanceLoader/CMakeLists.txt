cmake_minimum_required (VERSION 2.8)
project(InstanceLoader)

add_library(${PROJECT_NAME} InstanceLoader.cpp)

add_subdirectory(unittests)