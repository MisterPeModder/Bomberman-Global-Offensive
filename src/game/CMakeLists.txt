set(INCROOT ${INCROOT}/game)
set(SRCROOT ${SRCROOT}/game)

add_subdirectory(map)
add_subdirectory(settings)

set (SRC
	${SRC}
	${SRCROOT}/Game.cpp
	${SRCROOT}/Game.hpp
	${SRCROOT}/GameAction.hpp
	${SRCROOT}/User.cpp
	${SRCROOT}/User.hpp
	${SRCROOT}/Users.cpp
	${SRCROOT}/Users.hpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
