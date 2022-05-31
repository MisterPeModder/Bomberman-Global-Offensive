set(INCROOT ${INCROOT}/game)
set(SRCROOT ${SRCROOT}/game)

add_subdirectory(map)

set (SRC
	${SRC}
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
