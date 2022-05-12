set(INCROOT ${INCROOT}/localization)
set(SRCROOT ${SRCROOT}/localization)

set(SRC
	${SRC}
	${SRCROOT}/Localization.hpp
	${SRCROOT}/RessourceFile.hpp
	${SRCROOT}/RessourceString.hpp
	PARENT_SCOPE
)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
