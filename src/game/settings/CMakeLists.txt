set(INCROOT ${INCROOT}/settings)
set(SRCROOT ${SRCROOT}/settings)

set(SRC
    ${SRC}
    ${SRCROOT}/GamepadInput.cpp
    ${INCROOT}/GamepadInput.hpp
    ${SRCROOT}/Keybinds.cpp
    ${INCROOT}/Keybinds.hpp
    ${SRCROOT}/Profile.cpp
    ${INCROOT}/Profile.hpp
    ${SRCROOT}/Settings.cpp
    ${INCROOT}/Settings.hpp
    PARENT_SCOPE
)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE
)
