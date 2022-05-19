set(INCROOT ${INCROOT}/shapes)
set(SRCROOT ${SRCROOT}/shapes)

set(SRC
	${SRC}
    ${SRCROOT}/Rectangle.cpp
    ${SRCROOT}/Rectangle.hpp
    ${SRCROOT}/Circle.cpp
    ${SRCROOT}/Circle.hpp
    ${SRCROOT}/Cube.cpp
    ${SRCROOT}/Cube.hpp
    ${SRCROOT}/Pixel.cpp
    ${SRCROOT}/Pixel.hpp
    ${SRCROOT}/Sphere.cpp
    ${SRCROOT}/Sphere.hpp
    ${SRCROOT}/AShape.hpp
	PARENT_SCOPE)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
