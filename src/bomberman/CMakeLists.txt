set(INCROOT ${INCROOT}/bomberman)
set(SRCROOT ${SRCROOT}/bomberman)

set(SRC
	${SRC}
    ${INCROOT}/Profile.hpp
	PARENT_SCOPE
)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
