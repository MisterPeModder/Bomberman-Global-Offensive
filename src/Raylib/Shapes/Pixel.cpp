/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Pixel
*/

#include "Pixel.hpp"

namespace raylib
{
    namespace shapes
    {
        Pixel::Pixel(Color color, float x, float y)
        {
            _position.x = x;
            _position.y = y;
            _color = color;
        }

        Pixel::Pixel(Vector2 position, Color color)
        {
            _position.x = position.x;
            _position.y = position.y;
            _color = color;
        }

        Pixel::~Pixel() {}

        void Pixel::drawPixel(float posX, float posY, Color color) { DrawPixel(posX, posY, color); }

        void Pixel::drawPixelV(Vector2 position, Color color) { DrawPixelV(position, color); }

        void Pixel::setPixelColor(void *dstPtr, Color color, float format)
        {
            _color = color;
            SetPixelColor(dstPtr, color, format);
        }

        Color Pixel::getPixelColor(void *srcPtr, float format) { return GetPixelColor(srcPtr, format); }

    } // namespace shapes

} // namespace raylib
