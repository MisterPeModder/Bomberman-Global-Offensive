set(INCROOT ${INCROOT}/ecs)
set(SRCROOT ${SRCROOT}/ecs)

add_subdirectory(join)
add_subdirectory(resource)
add_subdirectory(storage)
add_subdirectory(system)
add_subdirectory(world)

set(SRC
	${SRC}
    ${INCROOT}/Component.hpp
    ${INCROOT}/Entity.hpp
    ${INCROOT}/join.hpp
    ${INCROOT}/Storage.hpp
    ${INCROOT}/World.hpp
	PARENT_SCOPE
)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
