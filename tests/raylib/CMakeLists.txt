set(SRCROOT ${SRCROOT}/raylib)

set(SRC)

add_subdirectory(text)

add_bomberman_test(
    NAME bm_test_raylib
    DISPLAY_NAME "Bomberman-Raylib-Tests"
    SOURCES ${SRC}
)
