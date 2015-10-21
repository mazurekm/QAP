CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(jsoncpp)

SET( JSONCPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

SET( PUBLIC_HEADERS
    ${JSONCPP_INCLUDE_DIR}/json/config.h
    ${JSONCPP_INCLUDE_DIR}/json/forwards.h
    ${JSONCPP_INCLUDE_DIR}/json/features.h
    ${JSONCPP_INCLUDE_DIR}/json/value.h
    ${JSONCPP_INCLUDE_DIR}/json/reader.h
    ${JSONCPP_INCLUDE_DIR}/json/writer.h
    ${JSONCPP_INCLUDE_DIR}/json/assertions.h
    ${JSONCPP_INCLUDE_DIR}/json/version.h
    )

SET(jsoncpp_sources
                ${CMAKE_CURRENT_SOURCE_DIR}/src/json_tool.h
                ${CMAKE_CURRENT_SOURCE_DIR}/src/json_reader.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/json_valueiterator.inl
                ${CMAKE_CURRENT_SOURCE_DIR}/src/json_value.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/json_writer.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in)

ADD_LIBRARY(${PROJECT_NAME} STATIC ${PUBLIC_HEADERS} ${jsoncpp_sources})