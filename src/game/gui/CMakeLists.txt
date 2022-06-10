set(INCROOT ${INCROOT}/gui)
set(SRCROOT ${SRCROOT}/gui)

add_subdirectory(components)

set (SRC
	${SRC}
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
