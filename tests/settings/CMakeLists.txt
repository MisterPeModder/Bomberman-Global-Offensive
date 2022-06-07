set(SRCROOT ${SRCROOT}/settings)

set(SRC
    ${SRCROOT}/test_GamepadInput.cpp
    ${SRCROOT}/test_Settings.cpp
)

add_bomberman_test(
    NAME bm_test_settings
    DISPLAY_NAME "Bomberman-Settings-Tests"
    WORKING_DIRECTORY "${SRCROOT}"
    SOURCES ${SRC}
)
