cmake_minimum_required (VERSION 2.8)
project(LocalSearch)

add_library(${PROJECT_NAME} LocalSearch.cpp Greedy.cpp Steepest.cpp)

target_link_libraries(${PROJECT_NAME} Strategy)

add_subdirectory(unittests)