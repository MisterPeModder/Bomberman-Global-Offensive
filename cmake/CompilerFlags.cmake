# Platform-specific compilation options

if (EMSCRIPTEN)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # Directly build the emscriptem HTML template.
endif()

# Enable Warnings
if (COMPILER_TYPE MATCHES "msvc")
    message(STATUS "Enabling MSVC-specific options")

    add_compile_options(
        "/W4" 
        "/WX"
    )
elseif (COMPILER_TYPE MATCHES "gcc")
    message(STATUS "Enabling GCC-specific options")

    add_compile_options(
        "-Wall" "-Wextra" "-Wshadow" "-pedantic" "-Wpointer-arith" 
        "-Wsuggest-final-methods" "-Wsuggest-final-types" "-Wsuggest-override"
        "$<$<CONFIG:RELEASE>:-O3;-Werror>"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
    )
elseif (COMPILER_TYPE MATCHES "clang")
    message(STATUS "Enabling Clang-specific options")

    add_compile_options(
        "-Wall" "-Wextra" "-Wshadow"
        "$<$<CONFIG:RELEASE>:-O3;-Werror>"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
    )
endif()