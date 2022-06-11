# Usage: # FIND_PACKAGE(raylib REQUIRED)
# [...]
# TARGET_LINK_LIBRARIES(target_name raylib)

CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
if (NOT raylib_FOUND)
    INCLUDE(FetchContent)

    if (EMSCRIPTEN)
        set(PLATFORM "Web" CACHE STRING "Set web platform" FORCE)
    endif()

    # When both a legacy GL library (e.g. `libGL.so`) and GLVND libraries
    # for OpenGL and GLX (e.g. `libOpenGL.so` and `libGLX.so`) are available,
    # set `OpenGL_GL_PREFERENCE` to `GLVND`.
    set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)
    cmake_policy(SET CMP0072 NEW)

    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
        URL_HASH MD5=7b4ffb9d3b6a01806be21a7cd93e2c53
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        SET(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        ADD_SUBDIRECTORY(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        SET(raylib_FOUND TRUE)
    endif()
endif()
