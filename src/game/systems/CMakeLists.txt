set(INCROOT ${INCROOT}/systems)
set(SRCROOT ${SRCROOT}/systems)

set(SRC
    ${SRC}
    ${INCROOT}/Animation.hpp
    ${INCROOT}/Model.hpp
    ${SRCROOT}/DrawText.hpp
    ${SRCROOT}/DrawText.cpp
    ${SRCROOT}/InputManager.hpp
    ${SRCROOT}/InputManager.cpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
