cmake_minimum_required (VERSION 2.8)

project(QAP)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

find_package (Boost COMPONENTS system filesystem program_options REQUIRED)

#add_subdirectory(Utils)
#add_subdirectory(Algorithms)

add_executable(${PROJECT_NAME} main.cpp AlgorithmFactory.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}
					  ${Boost_FILESYSTEM_LIBRARY}
					  ${Boost_SYSTEM_LIBRARY}
					  ${Boost_PROGRAM_OPTIONS_LIBRARY})

enable_testing()