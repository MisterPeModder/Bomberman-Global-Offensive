set(INCROOT ${INCROOT}/logger)
set(SRCROOT ${SRCROOT}/logger)

set(SRC
	${SRC}
    ${SRCROOT}/Logger.cpp
	${SRCROOT}/Logger.hpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
