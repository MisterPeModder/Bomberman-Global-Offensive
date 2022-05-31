set(SRCROOT ${SRCROOT}/ecs)

set(SRC
    ${SRCROOT}/tests_ecs.cpp
    ${SRCROOT}/tests_Join.cpp
)

add_subdirectory(world)

add_bomberman_test(
    NAME bm_test_ecs
    DISPLAY_NAME "Bomberman-ECS-Tests"
    SOURCES ${SRC}
)
