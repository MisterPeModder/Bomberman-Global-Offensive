set(INCROOT ${INCROOT}/textures)
set(SRCROOT ${SRCROOT}/textures)

set(SRC
    ${SRC}
    ${SRCROOT}/Image.cpp
    ${SRCROOT}/Image.hpp
    ${SRCROOT}/RenderTexture2D.cpp
    ${SRCROOT}/RenderTexture2D.hpp
    ${SRCROOT}/Texture2D.cpp
    ${SRCROOT}/Texture2D.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
