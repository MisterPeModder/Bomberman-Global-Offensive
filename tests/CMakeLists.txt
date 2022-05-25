set(INCROOT "${PROJECT_SOURCE_DIR}/tests")
set(SRCROOT "${PROJECT_SOURCE_DIR}/tests")

set(SRC
    ${SRCROOT}/tests_dummy.cpp
)

add_subdirectory(localization)

set(TARGET_NAME unit_test_bomberman)

include(CompilerFlags)

add_executable(${TARGET_NAME} ${SRC})
target_include_directories(${TARGET_NAME} PRIVATE  ${INCROOT})

source_group("" FILES ${SRC})
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "tests")

target_link_libraries(${TARGET_NAME} PRIVATE libbomberman gmock_main)

add_test(NAME "BombermanUnitTests" COMMAND ${TARGET_NAME} WORKING_DIRECTORY ${SRCROOT})
