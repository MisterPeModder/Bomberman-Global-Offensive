set(SRCROOT ${SRCROOT}/localization)

set(SRC
    ${SRCROOT}/test_ressource_file.cpp
)

add_bomberman_test(
    NAME bm_test_localization
    DISPLAY_NAME "Bomberman-Localization-Tests"
    WORKING_DIRECTORY "${SRCROOT}/.."
    SOURCES ${SRC}
)
