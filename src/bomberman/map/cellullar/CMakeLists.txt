set(INCROOT ${INCROOT}/cellullar)
set(SRCROOT ${SRCROOT}/cellullar)

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
