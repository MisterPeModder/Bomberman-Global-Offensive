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

#include "script/Mod.hpp"

#include <filesystem>
#include <memory>
#include <vector>
#include <string_view>

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

        /// Unsafe version of instance(). Only call this from the main thread.
        ///
        /// @returns The Engine instance.
        static Engine *rawInstance();

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

        /// Loads a script in the default mods directory.
        ///
        /// @param name The name of the script, minus the extension.
        void loadScript(std::string_view name);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Modding
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// @returns A new mod instance.
        Mod &addMod(std::string_view name, std::string_view description);

        Mod const *getMod(std::size_t modId) const noexcept;
        Mod *getMod(std::size_t modId) noexcept;

      private:
        static std::weak_ptr<Engine> _instance;
        static Engine *_rawInstance;

        std::vector<Mod> _mods;

        Engine();

        void _load(std::filesystem::path const &path);
        void _loadApi();
        void _delete();

#ifndef __EMSCRIPTEN__
        js_State *_state;
#endif // !defined(__EMSCRIPTEN__)
    };
} // namespace bmjs

#endif // !defined(SCRIPT_ENGINE_HPP_)
