project(mujs LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# The EXTERNAL_MUJS_SOURCE_DIR must be defined before
set(SRCROOT ${EXTERNAL_MUJS_SOURCE_DIR})

set(SRC ${SRCROOT}/one.c)

add_library(mujs STATIC ${SRC})
target_include_directories(mujs PUBLIC ${SRCROOT})
