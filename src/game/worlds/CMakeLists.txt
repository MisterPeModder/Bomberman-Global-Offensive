set(INCROOT ${INCROOT}/worlds)
set(SRCROOT ${SRCROOT}/worlds)

set (SRC
	${SRC}
	${SRCROOT}/GameWorld.hpp
	# ${SRCROOT}/MainWorld.hpp
	# ${SRCROOT}/SettingsWorld.hpp
	# ${SRCROOT}/SplashWorld.hpp
	# ${SRCROOT}/TestWorld.hpp
	${SRCROOT}/IWorld.hpp
	PARENT_SCOPE)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
