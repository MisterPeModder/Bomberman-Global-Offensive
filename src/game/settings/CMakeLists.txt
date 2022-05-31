set(INCROOT ${INCROOT}/settings)
set(SRCROOT ${SRCROOT}/settings)

set(SRC
	${SRC}
	${INCROOT}/Settings.hpp
	PARENT_SCOPE
)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE
)
