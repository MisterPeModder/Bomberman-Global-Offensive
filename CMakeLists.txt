cmake_minimum_required(VERSION 3.16.0)

project(Bomberman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(BUILD_TEST_SUITE OFF)
option(ENABLE_CODE_COVERAGE OFF)

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(DetectCompiler)

find_package(raylib REQUIRED)

add_subdirectory(src)

# Unit testing
if(BUILD_TEST_SUITE)
    # Check for GoogleTest
    find_package(googletest REQUIRED)

    # Disable error on Linux release builds
    if(COMPILER_TYPE MATCHES "gcc")
        target_compile_options(gtest PRIVATE "-Wno-error=restrict")
        target_compile_options(gmock PRIVATE "-Wno-error=restrict")
    endif()

    enable_testing()

    add_subdirectory(tests)
endif()

# Copy the Web files (html/js/wasm/...) into the web directory on install
if(EMSCRIPTEN)
    install(
        FILES ${PROJECT_BINARY_DIR}/src/bomberman.html
        CONFIGURATIONS Release
        DESTINATION web
        RENAME index.html
    )

    install(
        FILES
        ${PROJECT_BINARY_DIR}/src/bomberman.data
        ${PROJECT_BINARY_DIR}/src/bomberman.js
        ${PROJECT_BINARY_DIR}/src/bomberman.wasm
        CONFIGURATIONS Release
        DESTINATION web
    )
endif()
