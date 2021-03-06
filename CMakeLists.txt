cmake_minimum_required (VERSION 2.8)

project(QAP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
set(TEST_DIR ${PROJECT_BINARY_DIR}/Tests)

find_package (Boost COMPONENTS system filesystem program_options unit_test_framework REQUIRED)

add_definitions (-DBOOST_TEST_DYN_LINK)
enable_testing()


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/External/jsoncpp/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/External)

add_subdirectory(External)
add_subdirectory(Algorithms)
add_subdirectory(Utils)

add_executable(${PROJECT_NAME} 
				main.cpp 
				AlgorithmFactory.cpp 
				Mode.cpp 
				ModeFactory.cpp 
				IterationCostMode.cpp
				TimeMode.cpp
				StartEndCostMode.cpp
			)

target_link_libraries(${PROJECT_NAME}
					  ${Boost_SYSTEM_LIBRARY}
					  Algorithms
                      Utils)

file(COPY config.json DESTINATION ${PROJECT_BINARY_DIR})
file(COPY Resources DESTINATION ${PROJECT_BINARY_DIR})
