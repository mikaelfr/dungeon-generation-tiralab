# CMakeList.txt : CMake project for dungeon-generation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE SOURCES *.h *.cpp)

# Add source to this project's executable.
add_executable (dungeon-generation ${SOURCES})

# TODO: Add tests and install targets if needed.
