set(INCROOT ${INCROOT}/localization)
set(SRCROOT ${SRCROOT}/localization)

set(SRC
    ${SRC}
    ${SRCROOT}/Localization.cpp
    ${SRCROOT}/Localization.hpp
    ${SRCROOT}/ResourceFile.cpp
    ${SRCROOT}/ResourceFile.hpp
    ${SRCROOT}/Resources.hpp
    ${SRCROOT}/ResourceString.cpp
    ${SRCROOT}/ResourceString.hpp
    PARENT_SCOPE
)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
