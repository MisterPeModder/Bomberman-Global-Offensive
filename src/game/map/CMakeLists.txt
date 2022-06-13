set(INCROOT ${INCROOT}/map)
set(SRCROOT ${SRCROOT}/map)

add_subdirectory(cellular)

set(SRC
	${SRC}
	${SRCROOT}/Map.cpp
	${SRCROOT}/Map.hpp
	${SRCROOT}/CreateMap.cpp
	PARENT_SCOPE)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
