set(INCROOT ${INCROOT}/resource)
set(SRCROOT ${SRCROOT}/resource)

set(SRC
	${SRC}
    ${SRCROOT}/Entities.cpp
    ${INCROOT}/Entities.hpp
    ${INCROOT}/Resource.hpp
    ${SRCROOT}/Timer.cpp
    ${INCROOT}/Timer.hpp
	PARENT_SCOPE
)
