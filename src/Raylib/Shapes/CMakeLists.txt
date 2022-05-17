set(INCROOT ${INCROOT}/Shapes)
set(SRCROOT ${SRCROOT}/Shapes)

set(SRC
	${SRC}
    ${SRCROOT}/Rectangle.cpp
    ${SRCROOT}/Rectangle.hpp
    ${SRCROOT}/Pixel.cpp
    ${SRCROOT}/Pixel.hpp
	PARENT_SCOPE)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
