set(INCROOT ${INCROOT}/cellular)
set(SRCROOT ${SRCROOT}/cellular)

set(SRC
	${SRC}
	${SRCROOT}/Grid.cpp
	${SRCROOT}/Grid.hpp
	${SRCROOT}/Rule.cpp
	${SRCROOT}/Rule.hpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
