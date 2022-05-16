# Sources

set(INCROOT ${PROJECT_SOURCE_DIR}/src)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC
    ${SRCROOT}/dummy.cpp
    ${SRCROOT}/Raylib/Camera3D.cpp
    ${SRCROOT}/Raylib/Camera3D.hpp
    ${SRCROOT}/Raylib/Vector2.cpp
    ${SRCROOT}/Raylib/Vector2.hpp
    ${SRCROOT}/Raylib/Vector3.cpp
    ${SRCROOT}/Raylib/Vector3.hpp
    ${SRCROOT}/Raylib/Window.cpp
    ${SRCROOT}/Raylib/Window.hpp
)

set(INCDIRS ${INCROOT})

add_subdirectory(logger)

# Source groups are a feature in Visual Studio.
source_group("" FILES ${SRC})

# Targets
# 
# The project is split into a static library containing most of the code,
# and an executable containing the main function.
# This enables unit-testing, since testing against an executable result in linking errors
# due to the main function being defined twice.

set(LIB_NAME libbomberman)
set(TARGET_NAME bomberman)

include(CompilerFlags)

add_library(libbomberman ${SRC})

target_include_directories(${LIB_NAME} PRIVATE ${INCDIRS})
target_include_directories(${LIB_NAME} PUBLIC ${INCROOT})

add_executable(${TARGET_NAME} ${SRCROOT}/main.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE ${LIB_NAME} raylib)

# Copy the executable to the root.
# There is no executable in the web build, so it is disabled there.
if (NOT EMPSCRIPTEN)
    add_custom_command(TARGET ${TARGET_NAME} 
    	POST_BUILD
    	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> ${PROJECT_SOURCE_DIR})
endif()
