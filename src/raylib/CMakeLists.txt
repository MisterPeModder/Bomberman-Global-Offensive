set(INCROOT ${INCROOT}/raylib)
set(SRCROOT ${SRCROOT}/raylib)

add_subdirectory(shapes)
add_subdirectory(core)
add_subdirectory(textures)
add_subdirectory(model)

set(SRC
    ${SRC}
    ${SRCROOT}/logger.cpp
    ${INCROOT}/raylib.hpp
    ${SRCROOT}/text.cpp
    ${INCROOT}/text.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
