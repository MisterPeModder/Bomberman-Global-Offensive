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

#ifndef __EMSCRIPTEN__
    #include <mujs.h>
#endif // !defined(__EMSCRIPTEN__)

namespace bmjs
{
    /// Javascript Engine Wrapper.
    class Engine {
      public:
        Engine();
        /// Cannot copy.
        Engine(Engine const &) = delete;
        ~Engine();

      private:
#ifndef __EMSCRIPTEN__
        js_State *_state;
#endif // !defined(__EMSCRIPTEN__)
    };
} // namespace bmjs

#endif // !defined(SCRIPT_ENGINE_HPP_)
