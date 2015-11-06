cmake_minimum_required (VERSION 2.8) 

project(Utils)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CommandLineProcessor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/InstanceLoader)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Stopwatch)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SmartStopwatch)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ConfManager)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CsvHelper)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/StatisticsCalculator)

add_library(${PROJECT_NAME} link.cpp)

target_link_libraries(${PROJECT_NAME} CommandLineProcessor)
target_link_libraries(${PROJECT_NAME} InstanceLoader)
target_link_libraries(${PROJECT_NAME} Stopwatch)
target_link_libraries(${PROJECT_NAME} SmartStopwatch)
target_link_libraries(${PROJECT_NAME} ConfManager)
target_link_libraries(${PROJECT_NAME} CsvHelper)
target_link_libraries(${PROJECT_NAME} StatisticsCalculator)
