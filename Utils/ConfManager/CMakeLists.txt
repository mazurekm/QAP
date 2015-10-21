cmake_minimum_required (VERSION 2.8) 

project(ConfManager)

add_library(${PROJECT_NAME} ConfManager.cpp)

target_link_libraries( ${PROJECT_NAME} 
					   ${Boost_FILESYSTEM_LIBRARY}
	                   jsoncpp)

add_subdirectory(unittests)