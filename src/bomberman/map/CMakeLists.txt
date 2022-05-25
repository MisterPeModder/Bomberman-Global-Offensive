set(INCROOT ${INCROOT}/map)
set(SRCROOT ${SRCROOT}/map)

add_subdirectory(cellullar)

set(SRC
	${SRC}
	${SRCROOT}/Map.cpp
	${SRCROOT}/Map.hpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
