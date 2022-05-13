cmake_minimum_required(VERSION 3.17.0)

project(Bomberman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if (EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # Directly build the emscriptem HTML template.
endif()

find_package(raylib REQUIRED)

# Unit testing
if (BUILD_TEST_SUITE)
    # Check for criterion
    find_package(Criterion)
    if (CRITERION_FOUND)
        enable_testing()
    endif()
endif()

# Enable Warnings
if (MSVC)
    add_compile_options(
        "/W4" 
        "/WX"
    )
else()
    add_compile_options(
        "-Wall" "-Wextra" "-Wshadow"
        "$<$<CONFIG:RELEASE>:-O3;-Werror>"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
    )
    # Those are GCC-exclusive options,
    # We need to detect clang++ and set the appropriate ones 

    # add_compile_options(
    #     "-Wall" "-Wextra" "-Wshadow" "-pedantic" "-Wpointer-arith" 
    #     "-Wsuggest-final-methods" "-Wsuggest-final-types" "-Wsuggest-override"
    #     "$<$<CONFIG:RELEASE>:-O3;-Werror>"
    #     "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
    # )
endif()

add_subdirectory(src)

if ((BUILD_TEST_SUITE) AND (CRITERION_FOUND))
    add_subdirectory(tests)
endif()
