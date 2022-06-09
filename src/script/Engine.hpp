/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Engine
*/

/// @file
///
/// Javascript Engine Wrapper.

#ifndef SCRIPT_ENGINE_HPP_
#define SCRIPT_ENGINE_HPP_

#include <filesystem>

#ifndef __EMSCRIPTEN__
    #include <mujs.h>
#endif // !defined(__EMSCRIPTEN__)

namespace bmjs
{
    /// Javascript Engine Wrapper.
    class Engine {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Instantiation
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Engine();

        /// Cannot copy.
        Engine(Engine const &) = delete;

        ~Engine();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Loading
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// Runs the JavaScript file at @c path.
        ///
        /// @param path The path of the script.
        void load(std::filesystem::path const &path);

        /// Loads the built-in JS API.
        void loadApi();

        /// Loads a mod script.
        ///
        /// @param name The name of the script, minus the extension.
        void loadMod(std::string_view name);

      private:
#ifndef __EMSCRIPTEN__
        js_State *_state;
#endif // !defined(__EMSCRIPTEN__)
    };
} // namespace bmjs

#endif // !defined(SCRIPT_ENGINE_HPP_)
