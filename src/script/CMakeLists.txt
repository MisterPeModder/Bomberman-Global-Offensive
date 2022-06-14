set(INCROOT ${INCROOT}/script)
set(SRCROOT ${SRCROOT}/script)

add_subdirectory(api)

set(SRC
    ${SRC}
    ${SRCROOT}/Engine.cpp
    ${INCROOT}/Engine.hpp
    ${SRCROOT}/JsException.cpp
    ${INCROOT}/JsException.hpp
    ${SRCROOT}/Mod.cpp
    ${INCROOT}/Mod.hpp
    ${SRCROOT}/RegistryGuard.cpp
    ${INCROOT}/RegistryGuard.hpp
    ${INCROOT}/script.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
