set(INCROOT ${INCROOT}/resources)
set(SRCROOT ${SRCROOT}/resources)

set(SRC
    ${SRC}
    ${SRCROOT}/Engine.hpp
    ${SRCROOT}/AssetMap.hpp
    ${SRCROOT}/Engine.hpp
    ${SRCROOT}/GameClock.cpp
    ${SRCROOT}/GameClock.hpp
    ${SRCROOT}/Map.hpp
    ${SRCROOT}/RandomDevice.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
