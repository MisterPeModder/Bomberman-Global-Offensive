# Bomberman: Global Offensive
[![Build](https://img.shields.io/github/workflow/status/MisterPeModder/Bomberman-Global-Offensive/Build-Testing)](https://github.com/MisterPeModder/Bomberman-Global-Offensive/actions/workflows/ci.yml)
[![License](https://img.shields.io/github/license/MisterPeModder/Bomberman-Global-Offensive)](https://github.com/MisterPeModder/Bomberman-Global-Offensive)
[![Codecov](https://codecov.io/gh/MisterPeModder/Bomberman-Global-Offensive/branch/master/graph/badge.svg)](https://codecov.io/gh/MisterPeModder/Bomberman-Global-Offensive)

====

# Building

Required tools:
- CMake 3.17 (minimum)

## Command Line

For Linux:
```sh
# Configure the project
cmake -B build/release_unix .. -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Release

# Build the executable and libraries
cmake --build release_unix
```

For Emscripten (on Linux):  
Make sure you have the [emscriptem toolchain](https://emscripten.org/) installed and in your `PATH`.

```sh
# Configure the project
emcmake cmake -B build/release_web .. -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Release

# Build the executable and libraries
cmake --build release_web
```

## IDEs

The game may also be built with any IDE that has `CMakePresets.json` support, such as Visual Sudio, VSCode + CMake Tools, or CLion.
Note that for the web platform, the presets assume that the emscripten toolchain is installed at `/opt/emsdk`.


# Documentation

The documentation is available [online](https://misterpemodder.github.io/Bomberman-Global-Offensive/).

## Local

Required tools:
- Doxygen

on Linux:
```sh
# Run at the root of the project
doxygen

# Open the genrated pages
xdg-open doc/build/html/index.html
```
