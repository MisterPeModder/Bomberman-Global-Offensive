set(INCROOT ${INCROOT}/bomberman)
set(SRCROOT ${SRCROOT}/bomberman)

add_subdirectory(map)

set (SRC
	${SRC}
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
