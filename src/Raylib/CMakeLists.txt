set(INCROOT ${INCROOT}/Raylib)
set(SRCROOT ${SRCROOT}/Raylib)

add_subdirectory(Shapes)
add_subdirectory(Core)

set(SRC
${SRC}
PARENT_SCOPE)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
