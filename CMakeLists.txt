cmake_minimum_required(VERSION 3.17.0)

project(Bomberman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(raylib REQUIRED)

# Unit testing
if (BUILD_TEST_SUITE)
    # Check for criterion
    find_package(Criterion REQUIRED)
    enable_testing()
endif()

add_compile_options(
    "-Wall" "-Wextra" "-Wshadow" "-pedantic" "-Wpointer-arith" "-Wsuggest-final-methods"
    "-Wsuggest-final-types" "-Wsuggest-override"
    "$<$<CONFIG:RELEASE>:-O3;-Werror>"
    "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

add_subdirectory(src)

if (BUILD_TEST_SUITE)
    add_subdirectory(tests)
endif()
