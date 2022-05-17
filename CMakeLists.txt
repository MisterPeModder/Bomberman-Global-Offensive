cmake_minimum_required(VERSION 3.17.0)

project(Bomberman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(DetectCompiler)

find_package(raylib REQUIRED)

add_subdirectory(src)

# Unit testing
if (BUILD_TEST_SUITE)
    # Check for criterion
    find_package(Criterion)

    if (CRITERION_FOUND)
        enable_testing()

        add_subdirectory(tests)
    endif()
endif()
