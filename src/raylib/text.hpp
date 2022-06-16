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
    /// Appends an Unicode codepoint to the end of @b str.
    ///
    /// @note This function is not safe to call over multiple threads.
    ///
    /// @param str The string to modify.
    /// @param codepoint An Unicode codepoint.
    void pushUnicodeCodepoint(std::string &str, int codepoint);
} // namespace raylib::text

#endif // !defined(RAYLIB_TEXT_HPP_)
