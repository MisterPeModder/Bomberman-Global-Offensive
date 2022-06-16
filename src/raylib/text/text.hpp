/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Raylib text module
*/

#ifndef RAYLIB_TEXT_TEXT_HPP_
#define RAYLIB_TEXT_TEXT_HPP_

#include "raylib/core/Color.hpp"
#include "raylib/core/Vector2.hpp"

#include <utility>
#include <string_view>

/// Raylib text module.
namespace raylib::text
{
    /// Encodes an Unicode codepoint to UTF-8.
    ///
    /// @note This function is not safe to call over multiple threads.
    ///
    /// @param codepoint An Unicode codepoint.
    ///
    /// @returns The UTF-8 encoded version of @b codepoint.
    std::string_view codepointToUtf8(int codepoint) noexcept;

    //// Decodes the first UTF-8 codepoint in @b str.
    ///
    /// @param str An UTF-8 encoded string.
    ///
    /// @returns The decoded codepoint, followed by the number of bytes decoded.
    std::pair<int, std::size_t> utf8ToCodepoint(std::string_view str) noexcept;

} // namespace raylib::text

#endif // !defined(RAYLIB_TEXT_TEXT_HPP_)
