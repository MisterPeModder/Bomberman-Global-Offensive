set(INCROOT ${INCROOT}/system)
set(SRCROOT ${SRCROOT}/system)

set(SRC
    ${SRC}
    ${INCROOT}/System.hpp
    ${INCROOT}/SystemData.hpp
    ${SRCROOT}/SystemTag.cpp
    ${INCROOT}/SystemTag.hpp
    PARENT_SCOPE
)
