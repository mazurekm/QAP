cmake_minimum_required (VERSION 2.8) 

project(Utils)

add_subdirectory(FileParser)

add_library(${PROJECT_NAME} link.cpp)

target_link_libraries(FileParser)