/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Cube
*/

#include "Cube.hpp"

namespace raylib
{
    namespace shapes
    {
        Cube::Cube(raylib::core::Vector3f position, raylib::core::Vector3f size, raylib::core::Color color)
        {
            setPosition(position);
            setColor(color);
            setSize(size);
        }

        void Cube::draw() const { DrawCubeV(_position.asRaylib(), _size.asRaylib(), _color.asRaylib()); }

        void Cube::draw(raylib::core::Vector3f position, raylib::core::Vector3f size, raylib::core::Color color)
        {
            DrawCubeV(position.asRaylib(), size.asRaylib(), color.asRaylib());
        }

        void Cube::drawWires() const { DrawCubeWiresV(_position.asRaylib(), _size.asRaylib(), _color.asRaylib()); }

        void Cube::setSize(raylib::core::Vector3f size) { _size = size; }

        raylib::core::Vector3f Cube::getSize() const { return _size; }
    } // namespace shapes
} // namespace raylib
