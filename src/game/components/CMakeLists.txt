set(INCROOT ${INCROOT}/components)
set(SRCROOT ${SRCROOT}/components)

set (SRC
	${SRC}
	${SRCROOT}/Collidable.hpp
	${SRCROOT}/Controlable.hpp
	${SRCROOT}/Destructible.hpp
	${SRCROOT}/Living.hpp
	${SRCROOT}/Movable.hpp
	${SRCROOT}/Player.hpp
	${SRCROOT}/Position.hpp
	${SRCROOT}/Size.hpp
	${SRCROOT}/Textual.hpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
