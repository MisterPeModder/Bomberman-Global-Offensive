set(INCROOT ${INCROOT}/components)
set(SRCROOT ${SRCROOT}/components)

add_subdirectory(items)

set(SRC
    ${SRC}
    ${INCROOT}/Animation.hpp
    ${SRCROOT}/Bomb.cpp
    ${INCROOT}/Bomb.hpp
    ${SRCROOT}/BombNoClip.cpp
    ${INCROOT}/BombNoClip.hpp
    ${INCROOT}/Collidable.hpp
    ${INCROOT}/Color.hpp
    ${INCROOT}/Controlable.hpp
    ${INCROOT}/Cube.hpp
    ${INCROOT}/CubeColor.hpp
    ${INCROOT}/Destructible.hpp
    ${INCROOT}/Explosion.cpp
    ${INCROOT}/Explosion.hpp
    ${SRCROOT}/History.cpp
    ${INCROOT}/History.hpp
    ${SRCROOT}/Identity.cpp
    ${INCROOT}/Identity.hpp
    ${INCROOT}/Image.hpp
    ${SRCROOT}/KeyboardInput.cpp
    ${INCROOT}/KeyboardInput.hpp
    ${INCROOT}/Living.hpp
    ${INCROOT}/Model.hpp
    ${SRCROOT}/Player.cpp
    ${INCROOT}/Player.hpp
    ${INCROOT}/Position.hpp
    ${INCROOT}/Position2D.hpp
    ${INCROOT}/Rectangle.hpp
    ${INCROOT}/Reference.hpp
    ${INCROOT}/RotationAngle.hpp
    ${INCROOT}/RotationAxis.hpp
    ${INCROOT}/Scale.hpp
    ${INCROOT}/ScreenId.hpp
    ${INCROOT}/Sound.cpp
    ${INCROOT}/Sound.hpp
    ${INCROOT}/Size.hpp
    ${INCROOT}/Size2D.hpp
    ${SRCROOT}/Textual.hpp
    ${INCROOT}/Texture2D.hpp
    ${INCROOT}/UseCheck.hpp
    ${SRCROOT}/Velocity.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
