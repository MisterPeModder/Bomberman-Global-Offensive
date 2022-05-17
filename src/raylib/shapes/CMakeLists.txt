set(INCROOT ${INCROOT}/shapes)
set(SRCROOT ${SRCROOT}/shapes)

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
