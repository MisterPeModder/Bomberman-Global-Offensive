set(INCROOT ${INCROOT}/util)
set(SRCROOT ${SRCROOT}/util)

set(SRC
	${SRC}
	${INCROOT}/util.cpp
	${INCROOT}/util.hpp
	${SRCROOT}/BitSet.cpp
	${INCROOT}/BitSet.hpp
	PARENT_SCOPE
)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE
)
