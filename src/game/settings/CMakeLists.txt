set(INCROOT ${INCROOT}/settings)
set(SRCROOT ${SRCROOT}/settings)

set(SRC
	${SRC}
	${SRCROOT}/Settings.cpp
	${INCROOT}/Settings.hpp
	PARENT_SCOPE
)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE
)
