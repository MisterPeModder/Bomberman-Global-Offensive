# Platform-specific compilation options

# Enable Warnings
if(COMPILER_TYPE MATCHES "msvc")
    message(STATUS "Enabling MSVC-specific options")

    add_compile_options(
        "/W4"
        "/WX"
    )
elseif(COMPILER_TYPE MATCHES "gcc")
    message(STATUS "Enabling GCC-specific options")

    add_compile_options(
        "-Wall" "-Wextra" "-Wshadow" "-pedantic" "-Wpointer-arith"
        "-Wsuggest-override"
        "-Wno-unknown-pragmas"
        "$<$<CONFIG:RELEASE>:-O3;-Werror>"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
    )

    if(ENABLE_TEST_COVERAGE)
        add_compile_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
        add_link_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
    endif()
elseif(COMPILER_TYPE MATCHES "clang")
    message(STATUS "Enabling Clang-specific options")

    add_compile_options(
        "-Wall" "-Wextra" "-Wshadow"
        "-Wno-unknown-pragmas"
        "$<$<CONFIG:RELEASE>:-O3;-Werror>"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
    )

    if(EMSCRIPTEN)
        message(STATUS "Enabling Emscripten-specific options")

        add_compile_options(
            -fexceptions -sDISABLE_EXCEPTION_CATCHING=0 # Exceptions
            "$<$<CONFIG:DEBUG>:-gsource-map>" # Source maps
        )
        add_link_options(
            -sUSE_GLFW=3 -sWASM=1 -sEXPORTED_RUNTIME_METHODS=ccall,cwrap # Bindings
            -fexceptions -sDISABLE_EXCEPTION_CATCHING=0 -sASSERTIONS=1 # Exceptions
            -sALLOW_TABLE_GROWTH -sALLOW_MEMORY_GROWTH # Resource growth
            "$<$<CONFIG:DEBUG>:-gsource-map>" # Source maps
        )
        set(CMAKE_EXECUTABLE_SUFFIX ".html") # Build using a HTML shell template
    endif()
endif()

# enable BM_RELEASE define in release mode
if(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_definitions(BM_RELEASE=1)
endif()
