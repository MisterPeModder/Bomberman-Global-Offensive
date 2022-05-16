set(INCROOT ${PROJECT_SOURCE_DIR}/src)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC
    ${SRCROOT}/dummy.cpp
    ${SRCROOT}/Raylib/Core/Camera3D.cpp
    ${SRCROOT}/Raylib/Core/Camera3D.hpp
    ${SRCROOT}/Raylib/Core/Vector2.cpp
    ${SRCROOT}/Raylib/Core/Vector2.hpp
    ${SRCROOT}/Raylib/Core/Vector3.cpp
    ${SRCROOT}/Raylib/Core/Vector3.hpp
    ${SRCROOT}/Raylib/Core/Window.cpp
    ${SRCROOT}/Raylib/Core/Window.hpp
    ${SRCROOT}/Raylib/Core/Mouse.hpp
    ${SRCROOT}/Raylib/Core/Mouse.cpp
    ${SRCROOT}/Raylib/Core/Cursor.hpp
    ${SRCROOT}/Raylib/Core/Cursor.cpp
    ${SRCROOT}/Raylib/Shapes/Rectangle.cpp
    ${SRCROOT}/Raylib/Shapes/Rectangle.hpp
    ${SRCROOT}/Raylib/Shapes/Pixel.cpp
    ${SRCROOT}/Raylib/Shapes/Pixel.hpp
)

set(INCDIRS ${INCROOT})

source_group("" FILES ${SRC})

set(LIB_NAME libbomberman)
set(TARGET_NAME bomberman)

add_library(libbomberman ${SRC})

get_target_property(RAYLIB_INCLUDES raylib INCLUDE_DIRECTORIES)


target_include_directories(${LIB_NAME} PRIVATE ${INCDIRS})
target_include_directories(${LIB_NAME} PUBLIC ${INCROOT})
target_link_libraries(${LIB_NAME} PUBLIC raylib)


add_executable(${TARGET_NAME} ${SRCROOT}/main.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE ${LIB_NAME})




add_custom_command(TARGET ${TARGET_NAME} 
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> ${PROJECT_SOURCE_DIR})
