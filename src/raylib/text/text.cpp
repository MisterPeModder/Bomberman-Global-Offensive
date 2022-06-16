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
} // namespace raylib::text
