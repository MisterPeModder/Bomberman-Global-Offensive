set(SRCROOT ${SRCROOT}/raylib)

set(SRC
    ${SRCROOT}/test_text.cpp
)

add_bomberman_test(
    NAME bm_test_raylib
    DISPLAY_NAME "Bomberman-Raylib-Tests"
    SOURCES ${SRC}
)
