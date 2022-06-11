set(INCROOT ${INCROOT}/worlds)
set(SRCROOT ${SRCROOT}/worlds)

set (SRC
	${SRC}
	${SRCROOT}/MainWorld.cpp
	${SRCROOT}/SettingsWorld.cpp
	${SRCROOT}/SplashWorld.cpp
	${SRCROOT}/TestWorld.cpp
	${SRCROOT}/GameWorld.cpp
	PARENT_SCOPE)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
