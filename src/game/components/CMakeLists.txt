set(INCROOT ${INCROOT}/components)
set(SRCROOT ${SRCROOT}/components)

set (SRC
	${SRC}
	${SRCROOT}/Bomb.cpp
	${SRCROOT}/Bomb.hpp
	${SRCROOT}/Collidable.hpp
	${SRCROOT}/Controlable.hpp
	${SRCROOT}/Cube.hpp
	${SRCROOT}/CubeColor.hpp
	${SRCROOT}/Destructible.hpp
	${SRCROOT}/Living.hpp
	${SRCROOT}/Player.cpp
	${SRCROOT}/Player.hpp
	${SRCROOT}/Position.hpp
	${SRCROOT}/Size.hpp
	${SRCROOT}/Textual.hpp
	${SRCROOT}/Velocity.hpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
