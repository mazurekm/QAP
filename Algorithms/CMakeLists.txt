cmake_minimum_required (VERSION 2.8)

project(Algorithms)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Strategy)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Random)

add_library(${PROJECT_NAME} link.cpp)

target_link_libraries(${PROJECT_NAME} Random)