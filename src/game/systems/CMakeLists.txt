set(INCROOT ${INCROOT}/systems)
set(SRCROOT ${SRCROOT}/systems)

set (SRC
	${SRC}
	${SRCROOT}/DrawText.hpp
	${SRCROOT}/DrawText.cpp
	${SRCROOT}/InputManager.hpp
	${SRCROOT}/InputManager.cpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
