set(SRCROOT "${PROJECT_SOURCE_DIR}/tests")

set(SRC
    ${SRCROOT}/tests_dummy.cpp
)

set(TARGET_NAME unit_test_bomberman)

include(CompilerFlags)

add_executable(${TARGET_NAME} ${SRC})

source_group("" FILES ${SRC})
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "tests")

target_link_libraries(${TARGET_NAME} PRIVATE libbomberman ${CRITERION_LIBRARIES})

add_test(NAME "BombermanUnitTests" COMMAND ${TARGET_NAME})
