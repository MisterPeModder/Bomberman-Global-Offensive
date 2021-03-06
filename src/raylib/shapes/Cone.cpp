/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Cone
*/

#include "Cone.hpp"

namespace raylib
{
    namespace shapes
    {
        Cone::Cone(raylib::core::Vector3f position, float radiusBase, float radiusTop, float height, int slices,
            raylib::core::Color color)
        {
            setPosition(position);
            setColor(color);
            setRadius(radiusBase, radiusTop);
            setHeight(height);
            setSlices(slices);
        }

        void Cone::draw() const
        {
            DrawCylinder(_position.asRaylib(), _radiusTop, _radiusTop, _height, _slices, _color.asRaylib());
        }

        void Cone::drawWires() const
        {
            DrawCylinderWires(_position.asRaylib(), _radiusTop, _radiusBase, _height, _slices, _color.asRaylib());
        }

        void Cone::setRadius(float radius)
        {
            _radiusBase = radius;
            _radiusTop = radius;
        }

        void Cone::setRadius(float base, float top)
        {
            _radiusBase = base;
            _radiusTop = top;
        }

        float Cone::getBaseRadius() const { return _radiusBase; }

        float Cone::getTopRadius() const { return _radiusTop; }

        void Cone::setHeight(float height) { _height = height; }

        float Cone::getHeight() const { return _height; }

        void Cone::setSlices(int slices) { _slices = slices; }

        int Cone::getSlices() const { return _slices; }

        bool Cone::isCylinder() const { return _radiusBase == _radiusTop; }
    } // namespace shapes
} // namespace raylib