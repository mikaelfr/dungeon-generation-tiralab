﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project("dungeon_generator")

# Set C++17
set(CMAKE_CXX_STANDARD 17)

# Set CMake module path
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/simple2d)

# Enable testing
include(CTest)

# Include doctest helper function
include(doctest)

# Include sub-projects.
add_subdirectory("src")

# If testing enabled, include tests folder
if (BUILD_TESTING)
    add_subdirectory("tests")
endif()
