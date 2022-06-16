/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Raylib text module
*/

#include "raylib/text.hpp"

#include <string>

extern "C"
{
#include <raylib.h>
}

namespace raylib::text
{
    void pushUtf8Codepoint(std::string &str, int codepoint) noexcept
    {
        int byte_count;
        char const *encoded = CodepointToUTF8(codepoint, &byte_count);

        if (byte_count > 0)
            str.append(encoded, encoded + byte_count);
    }

    int popUtf8Codepoint(std::string &str) noexcept
    {
        int bytes;
        int codepoint;
        char const *buf = str.c_str() + str.size();

        if (str.size() > 0 && static_cast<unsigned char>(*(buf - 1)) < 128U) {
            codepoint = static_cast<int>(*(buf - 1));
            str.pop_back();
            return codepoint;
        } else if (str.size() > 1 && (codepoint = GetCodepoint(buf - 2, &bytes)) != '?') {
            str.erase(str.end() - 2, str.end());
            return codepoint;
        } else if (str.size() > 2 && (codepoint = GetCodepoint(buf - 3, &bytes)) != '?') {
            str.erase(str.end() - 3, str.end());
            return codepoint;
        } else if (str.size() > 3 && (codepoint = GetCodepoint(buf - 4, &bytes)) != '?') {
            str.erase(str.end() - 4, str.end());
            return codepoint;
        }
        return 0;
    }
} // namespace raylib::text
