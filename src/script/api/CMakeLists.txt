set(INCROOT ${INCROOT}/api)
set(SRCROOT ${SRCROOT}/api)

set(SRC
	${SRC}
	${INCROOT}/api.hpp
	${SRCROOT}/common.cpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
