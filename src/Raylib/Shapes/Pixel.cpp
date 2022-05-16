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

        Pixel::Pixel(float x, float y, Color color)
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

        void Pixel::draw() { DrawPixel(_position.x, _position.y, _color); }

        void Pixel::setColor(Color color, float format)
        {
            (void)format;
            _color = color;
        }

        Color Pixel::getColor(float format)
        {
            (void)format;
            return _color;
        }

        void Pixel::setPosition(Vector2 position)
        {
            _position = position;
        }

        Vector2 Pixel::getPosition()
        {
            return _position;
        }

    } // namespace shapes

} // namespace raylib
