set(INCROOT ${INCROOT}/items)
set(SRCROOT ${SRCROOT}/items)

set(SRC
    ${SRC}
    ${SRCROOT}/BombUp.cpp
    ${SRCROOT}/BombDown.cpp
    ${SRCROOT}/ChainBall.cpp
    ${SRCROOT}/FireDown.cpp
    ${SRCROOT}/FireUp.cpp
    ${SRCROOT}/InvertedControls.cpp
    ${SRCROOT}/Item.cpp
    ${SRCROOT}/Item.hpp
    ${SRCROOT}/ItemIdentifier.hpp
    ${SRCROOT}/KickShoes.cpp
    ${SRCROOT}/LandMine.cpp
    ${SRCROOT}/NoClip.cpp
    ${SRCROOT}/Punch.cpp
    ${SRCROOT}/SmokeGrenade.cpp
    ${SRCROOT}/SpeedShoes.cpp
    ${SRCROOT}/StunGrenade.cpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
