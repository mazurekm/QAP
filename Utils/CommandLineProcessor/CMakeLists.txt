cmake_minimum_required (VERSION 2.8) 

project(CommandLineProcessor)

add_library(${PROJECT_NAME} CommandLineProcessor.cpp)

target_link_libraries(${PROJECT_NAME}
					  ${Boost_PROGRAM_OPTIONS_LIBRARY}
					  ${Boost_FILESYSTEM_LIBRARY})