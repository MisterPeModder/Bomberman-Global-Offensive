set(INCROOT ${INCROOT}/components)
set(SRCROOT ${SRCROOT}/components)

set(SRC
    ${SRC}
    ${SRCROOT}/Checkable.cpp
    ${INCROOT}/Checkable.hpp
    ${SRCROOT}/Clickable.cpp
    ${INCROOT}/Clickable.hpp
    ${SRCROOT}/Console.cpp
    ${INCROOT}/Console.hpp
    ${INCROOT}/IWidgetComponent.hpp
    ${SRCROOT}/Widget.cpp
    ${INCROOT}/Widget.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
