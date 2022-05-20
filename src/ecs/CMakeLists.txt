set(INCROOT ${INCROOT}/ecs)
set(SRCROOT ${SRCROOT}/ecs)

add_subdirectory(storage)
add_subdirectory(world)

set(SRC
	${SRC}
    ${INCROOT}/Component.hpp
    ${INCROOT}/Entity.hpp
    ${INCROOT}/System.hpp
    ${INCROOT}/SystemData.hpp
    ${INCROOT}/Instances.hpp
	PARENT_SCOPE
)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
