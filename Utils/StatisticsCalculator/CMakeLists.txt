cmake_minimum_required (VERSION 2.8)
project(StatisticsCalculator)

add_library(${PROJECT_NAME} StatisticsCalculator.cpp)

add_subdirectory(unittests)
