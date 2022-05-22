set(INCROOT ${INCROOT}/model)
set(SRCROOT ${SRCROOT}/model)

set(SRC
	${SRC}
    ${SRCROOT}/Model.cpp
    ${SRCROOT}/Model.hpp
    ${SRCROOT}/BoundingBox.hpp
	PARENT_SCOPE)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
