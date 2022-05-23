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
        Cube::Cube(Vector3 position, Vector3 size, Color color)
        {
            setPosition(position);
            setColor(color);
            setSize(size);
        }

        void Cube::draw() const { DrawCubeV(_position, _size, _color); }

        void Cube::drawWires() const { DrawCubeWiresV(_position, _size, _color); }

        void Cube::setSize(Vector3 size) { _size = size; }

        Vector3 Cube::getSize() const { return _size; }
    } // namespace shapes
} // namespace raylib