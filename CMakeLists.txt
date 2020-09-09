# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project("dungeon_generator")

# Enable testing
include(CTest)

# Include doctest helper function
include("cmake/doctest.cmake")

# Include sub-projects.
add_subdirectory("src")

# If testing enabled, include tests folder
if (BUILD_TESTING)
    add_subdirectory("tests")
endif()
