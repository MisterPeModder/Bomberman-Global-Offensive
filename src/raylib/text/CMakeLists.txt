set(INCROOT ${INCROOT}/text)
set(SRCROOT ${SRCROOT}/text)

set(SRC
    ${SRC}
    ${SRCROOT}/Font.cpp
    ${INCROOT}/Font.hpp
    ${SRCROOT}/text.cpp
    ${INCROOT}/text.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
