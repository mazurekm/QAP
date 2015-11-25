cmake_minimum_required (VERSION 2.8)
project(EnhancedLocalSearch)

add_library(${PROJECT_NAME} EnhancedLocalSearch.cpp Metropolis.cpp TabuSearch.cpp)

target_link_libraries(${PROJECT_NAME} Strategy)
target_link_libraries(${PROJECT_NAME} TabuSearchHelpers)

add_subdirectory(unittests)
add_subdirectory(tabusearch_unittests)
add_subdirectory(TabuSearchHelpers)