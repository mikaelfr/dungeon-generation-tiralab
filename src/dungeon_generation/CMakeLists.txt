# CMakeList.txt : CMake project for dungeon-generation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Get all sources recursively
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "*.h" "*.cpp")

# Combine sources to a static library
add_library(${PROJECT_NAME}_lib STATIC ${LIB_SOURCES})
