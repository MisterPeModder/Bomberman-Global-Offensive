set(INCROOT ${INCROOT}/raylib)
set(SRCROOT ${SRCROOT}/raylib)

add_subdirectory(shapes)
add_subdirectory(core)
add_subdirectory(textures)
add_subdirectory(model)

set(SRC
    ${SRC}
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
