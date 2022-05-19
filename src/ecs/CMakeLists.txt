set(INCROOT ${INCROOT}/ecs)
set(SRCROOT ${SRCROOT}/ecs)

set(SRC
	${SRC}
    ${INCROOT}/Component.hpp
    ${INCROOT}/Entity.hpp
    ${INCROOT}/System.hpp
    ${INCROOT}/World.cpp
    ${INCROOT}/World.hpp
	PARENT_SCOPE
)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
