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
#include <memory>

#ifndef __EMSCRIPTEN__
    #include <mujs.h>
#endif // !defined(__EMSCRIPTEN__)

namespace bmjs
{
    /// Javascript Engine Wrapper.
    ///
    /// Only one instance of Engine may exist at any given time.
    class Engine {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Instantiation
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// Creates the instance of Engine, if it does not already exist.
        ///
        /// @returns The Engine instance.
        static std::shared_ptr<Engine> create();

        /// @returns The Engine instance, may not exist.
        static std::weak_ptr<Engine> instance();

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
        static std::weak_ptr<Engine> _instance;

        Engine();

#ifndef __EMSCRIPTEN__
        js_State *_state;
#endif // !defined(__EMSCRIPTEN__)
    };
} // namespace bmjs

#endif // !defined(SCRIPT_ENGINE_HPP_)
