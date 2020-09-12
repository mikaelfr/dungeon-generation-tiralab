# CMakeList.txt : CMake project for dungeon-generation, include source and define
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
target_include_directories(${PROJECT_NAME}_test PRIVATE ${PROJECT_SOURCE_DIR}/libs/doctest/)
target_include_directories(${PROJECT_NAME}_test PRIVATE ${PROJECT_SOURCE_DIR}/src/)

# Dynamically discover and add tests
doctest_discover_tests(${PROJECT_NAME}_test)

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
	include(CodeCoverage)
	setup_target_for_coverage_lcov(
		NAME ${PROJECT_NAME}_coverage 
		EXECUTABLE ${PROJECT_NAME}_test
		EXCLUDE "tests/*" "libs/*" "src/dungeon_generation.cpp" "src/dungeon_generation.h"
	)

	SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif()