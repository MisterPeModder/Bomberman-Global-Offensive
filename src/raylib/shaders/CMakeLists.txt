set(INCROOT ${INCROOT}/shaders)
set(SRCROOT ${SRCROOT}/shaders)

set(SRC
    ${SRC}
    ${SRCROOT}/Shader.cpp
    ${SRCROOT}/Shader.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
