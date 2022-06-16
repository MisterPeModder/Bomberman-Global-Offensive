/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Raylib text module
*/

#ifndef RAYLIB_TEXT_HPP_
#define RAYLIB_TEXT_HPP_

#include <string>

/// Raylib text module.
namespace raylib::text
{
    /// Appends an UTF-8 codepoint to the end of @b str.
    ///
    /// @note This function is not safe to call over multiple threads.
    ///
    /// @param str The string to modify.
    /// @param codepoint An Unicode codepoint.
    void pushUtf8Codepoint(std::string &str, int codepoint) noexcept;

    /// Removes the last UTF-8 codepoint from the end of @b str.
    ///
    /// @note This function is not safe to call over multiple threads.
    ///
    /// @param str The string to modify.
    ///
    /// @return The removed codepoint, or 0 if @b str was empty or not valid UTF-8.
    int popUtf8Codepoint(std::string &str) noexcept;
} // namespace raylib::text

#endif // !defined(RAYLIB_TEXT_HPP_)
