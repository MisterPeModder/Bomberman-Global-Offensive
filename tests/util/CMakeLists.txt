set(SRCROOT ${SRCROOT}/util)

set(SRC
    ${SRCROOT}/tests_BitSet.cpp
)

add_bomberman_test(
    NAME bm_test_util
    DISPLAY_NAME "Bomberman-Util-Tests"
    SOURCES ${SRC}
)
