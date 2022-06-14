set(INCROOT ${INCROOT}/scenes)
set(SRCROOT ${SRCROOT}/scenes)

set (SRC
${SRC}
	${INCROOT}/IScene.hpp
	${SRCROOT}/AScene.cpp
	${INCROOT}/AScene.hpp
	${INCROOT}/GameScene.hpp
	${SRCROOT}/MainScene.cpp
	${INCROOT}/MainScene.hpp
	${INCROOT}/SettingsScene.cpp
	${INCROOT}/SettingsScene.hpp
	${INCROOT}/SplashScene.cpp
	${INCROOT}/SplashScene.hpp
	${SRCROOT}/TestScene.cpp
	${INCROOT}/TestScene.hpp
	PARENT_SCOPE)

set(INCDIRS
	${INCDIRS}
	${INCROOT}
	PARENT_SCOPE)
