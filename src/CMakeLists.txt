# CMakeList.txt : CMake project for dungeon-generation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Include actual sources
add_subdirectory("dungeon_generation")

# On Windows we can just get away with copying dlls next to the exe
# but on linux we need to actually link the exe with all the libraries
if(UNIX)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)
    find_library(SIMPLE2D_LIB simple2d)
endif()

# Add main executable target and link sources
add_executable (${PROJECT_NAME} dungeon_generation.h dungeon_generation.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/libs/simple2d/)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)
if(UNIX)
    target_link_libraries(${PROJECT_NAME} ${SIMPLE2D_LIB} SDL2::Main SDL2::Image SDL2::Mixer SDL2::TTF GLEW::GLEW OpenGL::GL)
endif()
