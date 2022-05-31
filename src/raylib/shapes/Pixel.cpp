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
            setPosition(Vector2{x, y});
            setColor(color);
        }

        Pixel::Pixel(Vector2 position, Color color)
        {
            setPosition(position);
            setColor(color);
        }

        Pixel::~Pixel() {}

        void Pixel::draw() const { DrawPixel(_position.x, _position.y, _color); }
    } // namespace shapes

} // namespace raylib
