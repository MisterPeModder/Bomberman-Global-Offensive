# Usage: # FIND_PACKAGE(raylib REQUIRED)
# [...]
# TARGET_LINK_LIBRARIES(target_name raylib)

CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
if (NOT raylib_FOUND)
    INCLUDE(FetchContent)

    if (EMSCRIPTEN)
        set(PLATFORM "Web" CACHE STRING "Set web platform" FORCE)
    endif()

    FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz)
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        SET(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        ADD_SUBDIRECTORY(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        SET(raylib_FOUND TRUE)
    endif()
endif()
