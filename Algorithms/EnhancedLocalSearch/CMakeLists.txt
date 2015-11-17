cmake_minimum_required (VERSION 2.8)
project(EnhancedLocalSearch)

add_library(${PROJECT_NAME} EnhancedLocalSearch.cpp Metropolis.cpp )

target_link_libraries(${PROJECT_NAME} Strategy)

add_subdirectory(unittests)