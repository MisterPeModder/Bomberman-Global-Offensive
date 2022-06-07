set(INCROOT ${INCROOT}/game)
set(SRCROOT ${SRCROOT}/game)

add_subdirectory(components)
add_subdirectory(map)
add_subdirectory(settings)
add_subdirectory(systems)

set (SRC
	${SRC}
	${SRCROOT}/GameAction.hpp
	PARENT_SCOPE)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
