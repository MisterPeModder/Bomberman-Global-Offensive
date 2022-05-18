/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Color
*/

#include "Color.hpp"


namespace raylib
{
    namespace core
    {
        Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        {
            _color.r = r;
            _color.g = g;
            _color.b = b;
            _color.a = a;
        }

        Color::~Color()
        {
        }
    }
}
