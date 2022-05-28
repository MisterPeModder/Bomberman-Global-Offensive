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
        "-Wsuggest-override"
        "-Wno-unknown-pragmas"
        "$<$<CONFIG:RELEASE>:-O3;-Werror>"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
    )
    if (ENABLE_TEST_COVERAGE)
        add_compile_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
        add_link_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
    endif()
elseif (COMPILER_TYPE MATCHES "clang")
    message(STATUS "Enabling Clang-specific options")

    add_compile_options(
        "-Wall" "-Wextra" "-Wshadow"
        "-Wno-unknown-pragmas"
        "$<$<CONFIG:RELEASE>:-O3;-Werror>"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
        "-sNO_DISABLE_EXCEPTION_CATCHING"
    )

    if (EMSCRIPTEN)
        message(STATUS "Enabling Emscripten-specific options")

        add_compile_options("-sNO_DISABLE_EXCEPTION_CATCHING")
        add_link_options("-sNO_DISABLE_EXCEPTION_CATCHING")
    endif()
endif()

#enable BM_RELEASE define in release mode
if (CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_definitions(BM_RELEASE=1)
endif()
