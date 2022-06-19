set(INCROOT ${INCROOT}/api)
set(SRCROOT ${SRCROOT}/api)

set(SRC
    ${SRC}
    ${INCROOT}/api.hpp
    ${SRCROOT}/common.cpp
    ${SRCROOT}/mods.cpp
    ${SRCROOT}/players.cpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
