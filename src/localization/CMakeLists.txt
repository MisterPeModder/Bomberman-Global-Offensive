set(INCROOT ${INCROOT}/localization)
set(SRCROOT ${SRCROOT}/localization)

set(SRC
	${SRC}
	${SRCROOT}/Localization.cpp
	${SRCROOT}/Localization.hpp
	${SRCROOT}/RessourceFile.cpp
	${SRCROOT}/RessourceFile.hpp
	${SRCROOT}/Ressources.hpp
	${SRCROOT}/RessourceString.cpp
	${SRCROOT}/RessourceString.hpp
	PARENT_SCOPE
)

set(INCDIRS 
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
