set(INCROOT ${INCROOT}/worlds)
set(SRCROOT ${SRCROOT}/worlds)

set (SRC
	${SRC}
	${SRCROOT}/AWorld.cpp
	${INCROOT}/AWorld.hpp
	${INCROOT}/GameWorld.hpp
	# ${INCROOT}/MainWorld.hpp
	# ${INCROOT}/SettingsWorld.hpp
	# ${INCROOT}/SplashWorld.hpp
	${SRCROOT}/TestWorld.cpp
	${INCROOT}/TestWorld.hpp
	${INCROOT}/IWorld.hpp
	PARENT_SCOPE)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
