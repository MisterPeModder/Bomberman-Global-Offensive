CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

INCLUDE(FetchContent)

FetchContent_Declare(
    mujs
    URL https://mujs.com/downloads/mujs-1.2.0.zip
    URL_HASH MD5=3690b4ecfa43f6dfbc0711ac78172c1c
)

FetchContent_GetProperties(mujs)
if (NOT mujs_POPULATED)
    set(FETCHCONTENT_QUIET NO)

    FetchContent_Populate(mujs)
    set(EXTERNAL_MUJS_SOURCE_DIR ${mujs_SOURCE_DIR})
    add_subdirectory(${PROJECT_SOURCE_DIR}/cmake/mujs ${mujs_BINARY_DIR})
    set(mujs_FOUND TRUE)
endif()
