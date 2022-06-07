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
        Pixel::Pixel(float x, float y, raylib::core::Color color)
        {
            setPosition(raylib::core::Vector2{x, y});
            setColor(color);
        }

        Pixel::Pixel(raylib::core::Vector2 position, raylib::core::Color color)
        {
            setPosition(position);
            setColor(color);
        }

        Pixel::~Pixel() {}

        void Pixel::draw() const { DrawPixel(_position.x, _position.y, _color.asRaylib()); }
    } // namespace shapes

} // namespace raylib
