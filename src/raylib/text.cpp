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
    void pushUnicodeCodepoint(std::string &str, int codepoint)
    {
        int byte_count;
        char const *encoded = CodepointToUTF8(codepoint, &byte_count);

        if (byte_count > 0)
            str += encoded;
    }
} // namespace raylib::text
