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
        Sphere::Sphere(raylib::core::Vector3f position, float radius, raylib::core::Color color)
        {
            setPosition(position);
            setColor(color);
            setRadius(radius);
        }

        void Sphere::draw() const { DrawSphere(_position.asRaylib(), _radius, _color.asRaylib()); }

        void Sphere::draw(int rings, int slices) const
        {
            DrawSphereEx(_position.asRaylib(), _radius, rings, slices, _color.asRaylib());
        }

        void Sphere::drawWires(int rings, int slices) const
        {
            DrawSphereWires(_position.asRaylib(), _radius, rings, slices, _color.asRaylib());
        }

        float Sphere::getRadius() const { return _radius; }

        void Sphere::setRadius(float radius) { _radius = radius; }
    } // namespace shapes
} // namespace raylib
