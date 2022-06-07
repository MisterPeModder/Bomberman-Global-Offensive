set(INCROOT ${INCROOT}/menu)
set(SRCROOT ${SRCROOT}/menu)

set(SRC
    ${SRC}
    ${SRCROOT}/MainMenu.hpp
    ${SRCROOT}/MainMenu.cpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
