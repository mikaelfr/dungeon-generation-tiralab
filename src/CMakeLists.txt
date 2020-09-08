# CMakeList.txt : CMake project for dungeon-generation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Include actual sources
add_subdirectory("dungeon_generation")

# Add main executable target and link sources
add_executable (${PROJECT_NAME} dungeon_generation.h dungeon_generation.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)
