cmake_minimum_required (VERSION 2.8) 

project(metropolis_unittest)

set( EXECUTABLE_OUTPUT_PATH ${TEST_DIR} )

add_executable (${PROJECT_NAME} ${PROJECT_NAME}.cpp)

target_link_libraries (${PROJECT_NAME}
		${Boost_FILESYSTEM_LIBRARY}
		${Boost_SYSTEM_LIBRARY}
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )

target_link_libraries(${PROJECT_NAME} EnhancedLocalSearch) 
target_link_libraries(${PROJECT_NAME} Utils)

add_test(${PROJECT_NAME} ${TEST_DIR}/${PROJECT_NAME})
