set(INCROOT ${INCROOT}/game)
set(SRCROOT ${SRCROOT}/game)

add_subdirectory(components)
add_subdirectory(map)
add_subdirectory(settings)
add_subdirectory(systems)
add_subdirectory(resources)
add_subdirectory(gui)
add_subdirectory(scenes)

set(SRC
    ${SRC}
    ${SRCROOT}/Engine.cpp
    ${SRCROOT}/Engine.hpp
    ${SRCROOT}/Game.cpp
    ${SRCROOT}/Game.hpp
    ${SRCROOT}/GameAction.hpp
    ${SRCROOT}/User.cpp
    ${SRCROOT}/User.hpp
    ${SRCROOT}/Users.cpp
    ${SRCROOT}/Users.hpp
    ${INCROOT}/GameTimer.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
