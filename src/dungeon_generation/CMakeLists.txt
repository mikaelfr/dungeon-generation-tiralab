# CMakeList.txt : CMake project for dungeon-generation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Get all sources recursively
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "*.h" "*.cpp")

find_library(SIMPLE2D_LIB simple2d)
if (UNIX)
    find_library(SDL_LIB SDL)
    find_library(GLU_LIB GLU)
    find_library(GL_LIB GL)
endif()

# Combine sources to a static library
add_library(${PROJECT_NAME}_lib STATIC ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME}_lib PRIVATE ${PROJECT_SOURCE_DIR}/libs/simple2d/)
target_link_libraries(${PROJECT_NAME}_lib PRIVATE ${SDL_LIB})
target_link_libraries(${PROJECT_NAME}_lib PRIVATE ${GLU_LIB})
target_link_libraries(${PROJECT_NAME}_lib PRIVATE ${GL_LIB})
target_link_libraries(${PROJECT_NAME}_lib PRIVATE ${SIMPLE2D_LIB})
