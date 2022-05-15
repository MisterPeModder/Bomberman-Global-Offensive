/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Pixel
*/

#include "Pixel.hpp"

raylib::Shapes::Pixel::Pixel(Color color, int x, int y)
{
    _position.x = x;
    _position.y = y;
    _color = color;
}

raylib::Shapes::Pixel::Pixel(Vector2 position, Color color)
{
    _position.x = position.x;
    _position.y = position.y;
    _color = color;
}

raylib::Shapes::Pixel::~Pixel()
{
}

void raylib::Shapes::Pixel::drawPixel(int posX, int posY, Color color)
{
    DrawPixel(posX, posY, color);
}


void raylib::Shapes::Pixel::drawPixelV(Vector2 position, Color color)
{
    DrawPixelV(position, color);
}

void raylib::Shapes::Pixel::setPixelColor(void *dstPtr, Color color, int format)
{
    _color = color;
    SetPixelColor(dstPtr, color, format);
}

Color raylib::Shapes::Pixel::getPixelColor(void *srcPtr, int format)
{
    return GetPixelColor(srcPtr, format);
}