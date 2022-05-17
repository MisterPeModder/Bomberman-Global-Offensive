set(INCROOT ${INCROOT}/Core)
set(SRCROOT ${SRCROOT}/Core)

set(SRC
	${SRC}
    ${SRCROOT}/Camera3D.cpp
    ${SRCROOT}/Camera3D.hpp
    ${SRCROOT}/Vector2.cpp
    ${SRCROOT}/Vector2.hpp 
    ${SRCROOT}/Vector3.cpp
    ${SRCROOT}/Vector3.hpp
    ${SRCROOT}/Window.cpp
    ${SRCROOT}/Window.hpp
    ${SRCROOT}/Mouse.hpp
    ${SRCROOT}/Mouse.cpp
    ${SRCROOT}/Cursor.hpp
    ${SRCROOT}/Cursor.cpp
	PARENT_SCOPE)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
