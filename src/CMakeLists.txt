set(INCROOT ${PROJECT_SOURCE_DIR}/src)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC
    ${SRCROOT}/dummy.cpp
)

set(INCDIRS ${INCROOT})

add_subdirectory(localization)

source_group("" FILES ${SRC})

set(LIB_NAME libbomberman)
set(TARGET_NAME bomberman)

add_library(libbomberman ${SRC})

target_include_directories(${LIB_NAME} PRIVATE ${INCDIRS})
target_include_directories(${LIB_NAME} PUBLIC ${INCROOT})

add_executable(${TARGET_NAME} ${SRCROOT}/main.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE ${LIB_NAME})

add_custom_command(TARGET ${TARGET_NAME} 
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> ${PROJECT_SOURCE_DIR})
