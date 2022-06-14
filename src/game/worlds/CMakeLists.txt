set(INCROOT ${INCROOT}/worlds)
set(SRCROOT ${SRCROOT}/worlds)

set (SRC
	${SRC}
	${SRCROOT}/GameWorld.cpp
	${SRCROOT}/MainWorld.cpp
	${SRCROOT}/SettingsWorld.cpp
	${SRCROOT}/SplashWorld.cpp
	${SRCROOT}/TestWorld.cpp
	${SRCROOT}/Worlds.hpp
	PARENT_SCOPE)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
