set(INCROOT ${INCROOT}/components)
set(SRCROOT ${SRCROOT}/components)

set (SRC
	${SRC}
	${SRCROOT}/Checkable.hpp
	${SRCROOT}/Clickable.hpp
	${SRCROOT}/Widget.hpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
