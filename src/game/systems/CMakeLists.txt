set(INCROOT ${INCROOT}/systems)
set(SRCROOT ${SRCROOT}/systems)

set(SRC
    ${SRC}
    ${INCROOT}/Animation.hpp
    ${INCROOT}/Model.hpp
    ${SRCROOT}/ChangeCube.hpp
    ${SRCROOT}/Collision.hpp
    ${SRCROOT}/Collision.cpp
    ${SRCROOT}/DrawingCube.hpp
    ${SRCROOT}/DrawText.hpp
    ${SRCROOT}/DrawText.cpp
    ${SRCROOT}/InputManager.hpp
    ${SRCROOT}/InputManager.cpp
    ${SRCROOT}/Movement.hpp
    ${SRCROOT}/Movement.cpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
