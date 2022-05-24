set(INCROOT ${INCROOT}/model)
set(SRCROOT ${SRCROOT}/model)

set(SRC ${SRC}
    ${SRCROOT}/Model.cpp
    ${SRCROOT}/Model.hpp
    ${SRCROOT}/BoundingBox.cpp
    ${SRCROOT}/BoundingBox.hpp
    ${SRCROOT}/Animation.cpp
    ${SRCROOT}/Animation.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
