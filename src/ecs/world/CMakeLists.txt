set(INCROOT ${INCROOT}/world)
set(SRCROOT ${SRCROOT}/world)

set(SRC
	${SRC}
    ${INCROOT}/Entities.cpp
    ${INCROOT}/Entities.hpp
    ${INCROOT}/Resource.hpp
    ${SRCROOT}/World.cpp
    ${INCROOT}/World.hpp
	PARENT_SCOPE
)
