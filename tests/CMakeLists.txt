function(add_bomberman_test)
    # Declare arguments
    set(oneValueArgs NAME DISPLAY_NAME WORKING_DIRECTORY)
    set(multiValueArgs INCLUDE_DIRS SOURCES)
    cmake_parse_arguments(add_bomberman_test "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Check for required arguments NAME and SOURCES
    if(NOT DEFINED add_bomberman_test_NAME)
        message(FATAL_ERROR "missing unit test name")
    endif()

    if(NOT DEFINED add_bomberman_test_SOURCES)
        message(FATAL_ERROR "missing unit test sources")
    endif()

    # Define shorthand variables
    set(TARGET_NAME ${add_bomberman_test_NAME})
    set(SRC ${add_bomberman_test_SOURCES})
    set(INCDIRS ${add_bomberman_test_INCLUDE_DIRS})
    set(WORKING_DIRECTORY ${add_bomberman_test_WORKING_DIRECTORY})

    if(DEFINED add_bomberman_test_DISPLAY_NAME)
        set(DISPLAY_NAME ${add_bomberman_test_DISPLAY_NAME})
    else()
        set(DISPLAY_NAME ${TARGET_NAME})
    endif()

    # Add compiler flags
    include(CompilerFlags)

    # Create the test executable
    add_executable(${TARGET_NAME} ${SRC})
    target_include_directories(${TARGET_NAME} PRIVATE ${INCROOT})

    source_group(${TARGET_NAME} FILES ${SRC})
    set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "tests")

    target_link_libraries(${TARGET_NAME} PRIVATE libbomberman gmock_main raylib)

    # Register the test
    add_test(NAME "${DISPLAY_NAME}" COMMAND ${TARGET_NAME} WORKING_DIRECTORY ${WORKING_DIRECTORY})
endfunction()

set(INCROOT "${PROJECT_SOURCE_DIR}/tests")
set(SRCROOT "${PROJECT_SOURCE_DIR}/tests")

add_subdirectory(ecs)
add_subdirectory(util)
add_subdirectory(raylib)

# FIXME: #55 Re-enable localization tests on the web once we figure out how to bundle files
if(NOT EMSCRIPTEN)
    add_subdirectory(localization)
    add_subdirectory(settings)
endif()
