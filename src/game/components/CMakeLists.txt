set(INCROOT ${INCROOT}/components)
set(SRCROOT ${SRCROOT}/components)

set(SRC
    ${SRC}
    ${INCROOT}/Animation.hpp
    ${INCROOT}/Color.hpp
    ${INCROOT}/Model.hpp
    ${INCROOT}/Position.hpp
    ${INCROOT}/RotationAngle.hpp
    ${INCROOT}/RotationAxis.hpp
    ${INCROOT}/Scale.hpp
    ${INCROOT}/Size.hpp
    PARENT_SCOPE)

set(INCDIRS
    ${INCDIRS}
    ${INCROOT}
    PARENT_SCOPE)
