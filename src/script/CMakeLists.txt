set(INCROOT ${INCROOT}/script)
set(SRCROOT ${SRCROOT}/script)

add_subdirectory(api)

set(SRC
	${SRC}
	${SRCROOT}/bindings.cpp
	${SRCROOT}/Engine.cpp
	${INCROOT}/Engine.hpp
	${SRCROOT}/JsException.cpp
	${INCROOT}/JsException.hpp
	${INCROOT}/script.hpp
	PARENT_SCOPE)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE) 
