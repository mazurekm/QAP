cmake_minimum_required (VERSION 2.8)

project(Algorithms)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Strategy)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Random)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/LocalSearch)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/EnhancedLocalSearch)

add_library(${PROJECT_NAME} link.cpp)

target_link_libraries(${PROJECT_NAME} Random)
target_link_libraries(${PROJECT_NAME} LocalSearch)
target_link_libraries(${PROJECT_NAME} EnhancedLocalSearch)