set(INCROOT ${INCROOT}/systems)
set(SRCROOT ${SRCROOT}/systems)

set(SRC
    ${SRC}
    ${INCROOT}/Animation.hpp
    ${SRCROOT}/Bomb.cpp
    ${INCROOT}/Bomb.hpp
    ${INCROOT}/ChangeCube.hpp
    ${SRCROOT}/Collision.cpp
    ${INCROOT}/Collision.hpp
    ${INCROOT}/Cube.hpp
    ${INCROOT}/DrawingCube.hpp
    ${INCROOT}/DrawSelectedWidget.hpp
    ${SRCROOT}/DrawText.cpp
    ${INCROOT}/DrawText.hpp
    ${SRCROOT}/InputManager.cpp
    ${INCROOT}/InputManager.hpp
    ${SRCROOT}/Items.cpp
    ${INCROOT}/Items.hpp
    ${INCROOT}/Model.hpp
    ${SRCROOT}/Movement.cpp
    ${INCROOT}/Movement.hpp
    ${INCROOT}/NoClip.hpp
    ${INCROOT}/Rectangle.hpp
    ${SRCROOT}/UpdateInputFields.cpp
    ${INCROOT}/UpdateInputFields.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
