set(INCROOT ${INCROOT}/core)
set(SRCROOT ${SRCROOT}/core)

set(SRC
    ${SRC}
    ${SRCROOT}/Camera2D.cpp
    ${SRCROOT}/Camera2D.hpp
    ${SRCROOT}/Camera3D.cpp
    ${SRCROOT}/Camera3D.hpp
    ${SRCROOT}/Vector2.hpp
    ${SRCROOT}/Vector3.hpp
    ${SRCROOT}/Vector4.hpp
    ${SRCROOT}/Window.cpp
    ${SRCROOT}/Window.hpp
    ${SRCROOT}/Mouse.hpp
    ${SRCROOT}/scoped.hpp
    ${SRCROOT}/Cursor.hpp
    ${SRCROOT}/Cursor.cpp
    ${SRCROOT}/Color.hpp
    ${SRCROOT}/Color.cpp
    ${SRCROOT}/Audio.cpp
    ${INCROOT}/Audio.hpp
    ${INCROOT}/Sound.hpp
    ${SRCROOT}/Sound.cpp
    ${INCROOT}/Music.hpp
    ${SRCROOT}/Music.cpp
    ${SRCROOT}/Keyboard.hpp
    ${SRCROOT}/Keyboard.cpp
    ${SRCROOT}/Gamepad.hpp
    ${SRCROOT}/Gamepad.cpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
