set(INCROOT ${INCROOT}/scripting)
set(SRCROOT ${SRCROOT}/scripting)

set(SRC
	${SRC}
	${SRCROOT}/scripting.cpp
	${SRCROOT}/scripting.hpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
