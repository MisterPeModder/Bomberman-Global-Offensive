/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Main scripting header
*/

/// @file
///
/// Scripting interface utilities.

#ifndef SCRIPT_SCRIPT_HPP_
#define SCRIPT_SCRIPT_HPP_

// Supported Javascript types.
namespace bmjs
{
    /// Javascript string.
    using String = char const *;

    /// Javascript number.
    using Number = double;
} // namespace bmjs

/// Define the existence of an API group.
#define BMJS_DECLARE_API(name) void _bmjsKeepAlive_##name();

#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>

namespace bmjs
{
    /// JavaScript function reference.
    ///
    /// May throw instances of bmjs::JsException.
    ///
    /// @tparam R The return type.
    /// @tparam Args The argument types.
    template <typename R, typename... Args> using Function = R (*)(Args...);
} // namespace bmjs

    // clang-format off

    /// Start of API group declarations.
    #define BMJS_API_START(name) void _bmjsKeepAlive_##name() {} extern "C" {

    /// End of API group declarations.
    #define BMJS_API_END }

    /// Call this to prevent the API group @c name from being excluded from the binary.
    #define BMJS_USE_API(name) _bmjsKeepAlive_##name()

    /// Put this at the start of an API function.
    #define BMJS_DEFINE EMSCRIPTEN_KEEPALIVE

    // clang-format on
#else
    #include <functional>
    #include <mujs.h>

namespace bmjs
{
    /// JavaScript function reference.
    ///
    /// May throw instances of bmjs::JsException.
    ///
    /// @tparam R The return type.
    /// @tparam Args The argument types.
    template <typename R, typename... Args> using Function = std::function<R(Args...)>;
} // namespace bmjs

    // clang-format off

    /// Start of API group declarations.
    #define BMJS_API_START(name)

    /// End of API group declarations.
    #define BMJS_API_END

    /// Call this to prevent the api group @c name from being excluded from the binary.
    #define BMJS_USE_API(name)

    /// Put this at the start of an API function.
    #define BMJS_DEFINE

    // clang-format on
#endif // defined(__EMSCRIPTEN__)

#endif // !defined(SCRIPT_SCRIPT_HPP_)
