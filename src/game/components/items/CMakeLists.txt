set(INCROOT ${INCROOT}/items)
set(SRCROOT ${SRCROOT}/items)

set(SRC
    ${SRC}
    ${SRCROOT}/BombUp.cpp
    ${SRCROOT}/ChainBall.cpp
    ${SRCROOT}/FireUp.cpp
    ${SRCROOT}/Item.cpp
    ${SRCROOT}/Item.hpp
    ${SRCROOT}/ItemIdentifier.hpp
    ${SRCROOT}/KickShoes.cpp
    ${SRCROOT}/SpeedShoes.cpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
