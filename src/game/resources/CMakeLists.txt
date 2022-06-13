set(INCROOT ${INCROOT}/resources)
set(SRCROOT ${SRCROOT}/resources)

set (SRC
	${SRC}
	${SRCROOT}/Map.hpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
