set(INCROOT ${INCROOT}/components)
set(SRCROOT ${SRCROOT}/components)

set (SRC
	${SRC}
	${SRCROOT}/Controlable.hpp
	${SRCROOT}/Textual.hpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
