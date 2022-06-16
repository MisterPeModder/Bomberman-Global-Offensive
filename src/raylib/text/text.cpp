/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Raylib text module
*/

#include "raylib/text/text.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/core/Vector2.hpp"
#include "raylib/text/Font.hpp"

#include <string>

extern "C"
{
#include <raylib.h>
}

namespace raylib::text
{
    std::string_view codepointToUtf8(int codepoint) noexcept
    {
        int byteCount;
        char const *encoded = CodepointToUTF8(codepoint, &byteCount);

        return std::string_view(encoded, byteCount);
    }

    std::pair<int, std::size_t> utf8ToCodepoint(std::string_view str) noexcept
    {
        int byteCount;
        int codepoint = ::GetCodepoint(str.data(), &byteCount);

        return {codepoint, byteCount};
    }

    void draw(std::string_view str, raylib::core::Vector2f pos, float fontSize, raylib::core::Color tint)
    {
        Font font(Font::getDefault());

        // Check if default font has been loaded
        if (font.asRaylib().texture.id != 0) {
            int defaultFontSize = 10; // Default Font chars height in pixel
            if (fontSize < defaultFontSize)
                fontSize = defaultFontSize;
            int spacing = fontSize / defaultFontSize;

            draw(font, str, pos, fontSize, spacing, tint);
        }
    }

    void draw(Font const &font, std::string_view str, raylib::core::Vector2f pos, float fontSize, float spacing,
        raylib::core::Color tint)
    {
        ::DrawTextEx(font.asRaylib(), str.data(), pos.asRaylib(), fontSize, spacing, tint.asRaylib());
    }

    void draw(Font const &font, std::string_view str, raylib::core::Vector2f pos, raylib::core::Vector2f origin,
        float rotation, float fontSize, float spacing, raylib::core::Color tint)
    {
        ::DrawTextPro(font.asRaylib(), str.data(), pos.asRaylib(), origin.asRaylib(), rotation, fontSize, spacing,
            tint.asRaylib());
    }

    void draw(Font const &font, int codepoint, raylib::core::Vector2f pos, float fontSize, raylib::core::Color tint)
    {
        ::DrawTextCodepoint(font.asRaylib(), codepoint, pos.asRaylib(), fontSize, tint.asRaylib());
    }
} // namespace raylib::text
