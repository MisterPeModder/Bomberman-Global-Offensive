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
    class Font;

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

    /// Draws the text @b str at @b pos with a size of @b fontSize with a color of @c tint using the default font.
    ///
    /// @param str The text to render.
    /// @param pos Where to draw the text.
    /// @param fontSize The size of the font.
    /// @param tint The color of the text.
    void draw(std::string_view str, raylib::core::Vector2f pos, float fontSize, raylib::core::Color tint);

    /// Draws the text @b str at @b pos with a size of @b fontSize with a color of @c tint using the passed font.
    ///
    /// @param font The font to use.
    /// @param str The text to render.
    /// @param pos Where to draw the text.
    /// @param fontSize The size of the font.
    /// @param spacing The padding between each character.
    /// @param tint The color of the text.
    void draw(Font const &font, std::string_view str, raylib::core::Vector2f pos, float fontSize, float spacing,
        raylib::core::Color tint);

    /// Draws the text @b str at @b pos with a size of @b fontSize with a color of @c tint using the passed font.
    /// Allows the rendered text to be rotated.
    ///
    /// @param font The font to use.
    /// @param str The text to render.
    /// @param pos Where to draw the text.
    /// @param origin The rotation origin position.
    /// @param rotation The rotation.
    /// @param fontSize The size of the font.
    /// @param spacing The padding between each character.
    /// @param tint The color of the text.
    void draw(Font const &font, std::string_view str, raylib::core::Vector2f pos, raylib::core::Vector2f origin,
        float rotation, float fontSize, float spacing, raylib::core::Color tint);

    /// Draws the codepoint str at @b pos with a size of @b fontSize with a color of @c tint using the passed font.
    ///
    /// @param font The font to use.
    /// @param codepoint The Unicode codepoint to render
    /// @param pos Where to draw the text.
    /// @param fontSize The size of the font.
    /// @param tint The color of the text.
    void draw(Font const &font, int codepoint, raylib::core::Vector2f pos, float fontSize, raylib::core::Color tint);
} // namespace raylib::text

#endif // !defined(RAYLIB_TEXT_TEXT_HPP_)
