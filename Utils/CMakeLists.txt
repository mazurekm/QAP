cmake_minimum_required (VERSION 2.8) 

project(Utils)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/FileParser)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CommandLineProcessor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Instance)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/InstanceLoader)

add_library(${PROJECT_NAME} link.cpp)

target_link_libraries(${PROJECT_NAME} FileParser)
target_link_libraries(${PROJECT_NAME} CommandLineProcessor)
target_link_libraries(${PROJECT_NAME} Instance)
target_link_libraries(${PROJECT_NAME} InstanceLoader)
