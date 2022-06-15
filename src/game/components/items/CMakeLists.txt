set(INCROOT ${INCROOT}/items)
set(SRCROOT ${SRCROOT}/items)

set(SRC
    ${SRC}
    ${SRCROOT}/ChainBall.cpp
    ${SRCROOT}/Item.cpp
    ${SRCROOT}/Item.hpp
    ${SRCROOT}/ItemIdentifier.hpp
    ${SRCROOT}/SpeedShoes.cpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
