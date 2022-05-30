/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Sphere
*/

#include "Sphere.hpp"

namespace raylib
{
    namespace shapes
    {
        Sphere::Sphere(Vector3 position, float radius, Color color)
        {
            setPosition(position);
            setColor(color);
            setRadius(radius);
        }

        void Sphere::draw() const { DrawSphere(_position, _radius, _color); }

        void Sphere::draw(int rings, int slices) const { DrawSphereEx(_position, _radius, rings, slices, _color); }

        void Sphere::drawWires(int rings, int slices) const
        {
            DrawSphereWires(_position, _radius, rings, slices, _color);
        }

        float Sphere::getRadius() const { return _radius; }

        void Sphere::setRadius(float radius) { _radius = radius; }
    } // namespace shapes
} // namespace raylib
