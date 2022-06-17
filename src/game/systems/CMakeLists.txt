set(INCROOT ${INCROOT}/systems)
set(SRCROOT ${SRCROOT}/systems)

set(SRC
    ${SRC}
    ${SRCROOT}/Bomb.hpp
    ${SRCROOT}/Bomb.cpp
    ${INCROOT}/Animation.hpp
    ${INCROOT}/Model.hpp
    ${SRCROOT}/Cube.hpp
    ${SRCROOT}/ChangeCube.hpp
    ${SRCROOT}/Collision.hpp
    ${SRCROOT}/Collision.cpp
    ${INCROOT}/DrawTexture.hpp
    ${SRCROOT}/DrawingCube.hpp
    ${INCROOT}/DrawSelectedWidget.hpp
    ${SRCROOT}/DrawText.hpp
    ${SRCROOT}/DrawText.cpp
    ${SRCROOT}/InputManager.hpp
    ${SRCROOT}/InputManager.cpp
    ${SRCROOT}/Items.cpp
    ${SRCROOT}/Items.hpp
    ${SRCROOT}/Movement.hpp
    ${SRCROOT}/Movement.cpp
    ${SRCROOT}/Rectangle.hpp
    ${INCROOT}/SplashScreen.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
