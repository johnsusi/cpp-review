cmake_minimum_required(VERSION 3.28.3)

project(RockSolidJson
    LANGUAGES CXX
    DESCRIPTION "A JSON parser for C++"
    VERSION 1.0.0
)

add_subdirectory(src/json)

include(CTest)

if(BUILD_TESTING AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(test)
endif()