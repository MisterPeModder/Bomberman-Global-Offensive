set(SRCROOT ${SRCROOT}/util)

set(SRC
    ${SRCROOT}/tests_BitSet.cpp
    ${SRCROOT}/tests_util.cpp
)

if(NOT EMSCRIPTEN)
    set(SRC
        ${SRCROOT}/test_loadConfigFile.cpp
    )
endif()

add_bomberman_test(
    NAME bm_test_util
    DISPLAY_NAME "Bomberman-Util-Tests"
    WORKING_DIRECTORY "${SRCROOT}"
    SOURCES ${SRC}
)
