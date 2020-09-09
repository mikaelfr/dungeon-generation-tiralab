﻿# CMakeList.txt : CMake project for dungeon-generation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Recursively get all test source files
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "*.h" "*.cpp")

# Create target for tests
add_executable(${PROJECT_NAME}_test ${TEST_SOURCES})

# Link library to tests
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib)

# Set properties for test target
target_include_directories(${PROJECT_NAME}_test PUBLIC "../libs/doctest/")
target_include_directories(${PROJECT_NAME}_test PUBLIC "../src/")

# Dynamically discover and add tests
doctest_discover_tests(${PROJECT_NAME}_test)