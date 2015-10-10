cmake_minimum_required (VERSION 2.8)
project(Random)

add_library(${PROJECT_NAME} Random.cpp)

target_link_libraries(${PROJECT_NAME} Strategy)

add_subdirectory(unittests)