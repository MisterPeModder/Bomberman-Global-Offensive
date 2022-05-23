set(SRCROOT ${SRCROOT}/ecs)

add_subdirectory(world)

set(SRC
    ${SRC}
    ${SRCROOT}/tests_ecs.cpp
    PARENT_SCOPE
)
