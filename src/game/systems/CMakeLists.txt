set(INCROOT ${INCROOT}/systems)
set(SRCROOT ${SRCROOT}/systems)

set(SRC
    ${SRC}
    ${SRCROOT}/AiUpdate.cpp
    ${INCROOT}/AiUpdate.hpp
    ${INCROOT}/Animation.hpp
    ${SRCROOT}/Bomb.cpp
    ${INCROOT}/Bomb.hpp
    ${INCROOT}/ChangeCube.hpp
    ${SRCROOT}/Collision.cpp
    ${INCROOT}/Collision.hpp
    ${INCROOT}/Cube.hpp
    ${SRCROOT}/DrawConsole.cpp
    ${INCROOT}/DrawConsole.hpp
    ${SRCROOT}/DrawFpsCounter.cpp
    ${INCROOT}/DrawFpsCounter.hpp
    ${INCROOT}/DrawingCube.hpp
    ${INCROOT}/DrawSelectedWidget.hpp
    ${SRCROOT}/DrawText.cpp
    ${INCROOT}/DrawText.hpp
    ${INCROOT}/DrawTexture.hpp
    ${INCROOT}/DrawTextureBackground.hpp
    ${SRCROOT}/InputManager.cpp
    ${INCROOT}/InputManager.hpp
    ${SRCROOT}/Items.cpp
    ${INCROOT}/Items.hpp
    ${INCROOT}/Model.hpp
    ${SRCROOT}/Movement.cpp
    ${INCROOT}/Movement.hpp
    ${INCROOT}/NoClip.hpp
    ${INCROOT}/PlaySoundOnce.hpp
    ${INCROOT}/Rectangle.hpp
    ${SRCROOT}/Smoke.cpp
    ${INCROOT}/Smoke.hpp
    ${INCROOT}/SplashScreen.hpp
    ${SRCROOT}/UpdateKeyboardInput.cpp
    ${INCROOT}/UpdateKeyboardInput.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
