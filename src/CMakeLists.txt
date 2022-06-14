# Sources

set(INCROOT ${PROJECT_SOURCE_DIR}/src)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC ${SRCROOT}/bindings.cpp)

set(INCDIRS ${INCROOT})

add_subdirectory(ecs)
add_subdirectory(localization)
add_subdirectory(logger)
add_subdirectory(raylib)
add_subdirectory(script)
add_subdirectory(util)
add_subdirectory(game)

# Source groups are a feature in Visual Studio.
source_group("" FILES ${SRC})

# Targets
#
# The project is split into a static library containing most of the code,
# and an executable containing the main function.
# This enables unit-testing, since testing against an executable result in linking errors
# due to the main function being defined twice.
set(GENERATOR_NAME bomberman-generate-bindings)
set(LIB_NAME libbomberman)
set(TARGET_NAME bomberman)

# Generate the JS to C++ bindings
set(GENERATED_SRC ${SRCROOT}/bindings.cpp ${SRCROOT}/bindings.js)
add_custom_target(
    ${GENERATOR_NAME}
    BYPRODUCTS ${GENERATED_SRC}
    COMMAND python3 ${PROJECT_SOURCE_DIR}/generate_bindings.py ${SRCROOT}/script/api ${GENERATED_SRC}
    VERBATIM
)

include(CompilerFlags)

add_library(${LIB_NAME} ${SRC})
add_dependencies(${LIB_NAME} ${GENERATOR_NAME})

target_include_directories(${LIB_NAME} PRIVATE ${INCDIRS})
target_include_directories(${LIB_NAME} PUBLIC ${INCROOT})

target_link_libraries(${LIB_NAME} PUBLIC raylib)

add_executable(${TARGET_NAME} ${SRCROOT}/main.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE ${LIB_NAME} raylib)

if(NOT EMSCRIPTEN)
    find_package(mujs REQUIRED)

    target_link_libraries(${LIB_NAME} PUBLIC mujs)
    target_link_libraries(${TARGET_NAME} PRIVATE ${LIB_NAME} mujs)
endif()

if(EMSCRIPTEN)
    # Use our HTML shell instead of the default one provided by Emscripten
    target_link_options(${TARGET_NAME} PUBLIC --shell-file ${SRCROOT}/shell.html)

    # Embed the browser JS API bindings
    target_link_options(${TARGET_NAME} PUBLIC "SHELL:--post-js ${SRCROOT}/bindings.js")

    # Preload the API
    target_link_options(${TARGET_NAME} PUBLIC "SHELL:--post-js ${PROJECT_SOURCE_DIR}/mods/api.js")

    # Make the contents of the mods directory available at the root of the site
    target_link_options(${TARGET_NAME} PUBLIC "SHELL:--preload-file ${PROJECT_SOURCE_DIR}/mods@mods")

    # Make the contents of the assets directory available at the root of the site
    target_link_options(${TARGET_NAME} PUBLIC "SHELL:--preload-file ${PROJECT_SOURCE_DIR}/assets@assets")
endif()

# Copy the executable to the root.
# There is no executable in the web build, so it is disabled there.
if(NOT EMSCRIPTEN)
    add_custom_command(TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> ${PROJECT_SOURCE_DIR})
endif()
