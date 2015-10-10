cmake_minimum_required (VERSION 2.8)
project(Strategy)

add_library(${PROJECT_NAME} Strategy.cpp)
target_link_libraries(${PROJECT_NAME} Utils)