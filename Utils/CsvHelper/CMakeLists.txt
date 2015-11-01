cmake_minimum_required (VERSION 2.8)
project(CsvHelper)

add_library(${PROJECT_NAME} CsvHelper.cpp)

target_link_libraries(${PROJECT_NAME} minicsv)