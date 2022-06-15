set(INCROOT ${INCROOT}/components)
set(SRCROOT ${SRCROOT}/components)

set(SRC
    ${SRC}
    ${SRCROOT}/Bomb.cpp
    ${SRCROOT}/Bomb.hpp
    ${SRCROOT}/Collidable.hpp
    ${SRCROOT}/Controlable.hpp
    ${SRCROOT}/Textual.hpp
    ${INCROOT}/Animation.hpp
    ${INCROOT}/Color.hpp
    ${SRCROOT}/Identity.cpp
    ${SRCROOT}/Identity.hpp
    ${INCROOT}/Image.hpp
    ${INCROOT}/Model.hpp
    ${INCROOT}/Position.hpp
    ${INCROOT}/RotationAngle.hpp
    ${INCROOT}/RotationAxis.hpp
    ${INCROOT}/Scale.hpp
    ${INCROOT}/Size.hpp
    ${INCROOT}/Texture2D.hpp
    ${INCROOT}/Rectangle.hpp
    ${SRCROOT}/Velocity.hpp
    ${SRCROOT}/Living.hpp
    ${SRCROOT}/Player.cpp
    ${SRCROOT}/Destructible.hpp
    ${SRCROOT}/Cube.hpp
    ${SRCROOT}/CubeColor.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
