/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Circle
*/

#include "Circle.hpp"

namespace raylib
{
    namespace shapes
    {

        Circle::Circle(float x, float y, float z, float radius, Color color)
        {
            _x = x;
            _y = y;
            _z = z;
            _radius = radius;
            _color = color;
        }

        void Circle::draw() { DrawCircle(_x, _y, _radius, _color); }

        void Circle::drawSector(float startAngle, float endAngle, float segments, Color color)
        {
            DrawCircleSector({_x, _y}, _radius, startAngle, endAngle, segments, color);
        }

        void Circle::drawSectorLines(float startAngle, float endAngle, float segments, Color color)
        {
            DrawCircleSectorLines({_x, _y}, _radius, startAngle, endAngle, segments, color);
        }

        void Circle::drawGradient(Color color1, Color color2) { DrawCircleGradient(_x, _y, _radius, color1, color2); }

        void Circle::drawLines(Color color) { DrawCircleLines(_x, _y, _radius, color); }

        bool Circle::checkCollisions(Circle *other)
        {
            return CheckCollisionCircles({_x, _y}, _radius, {other->_x, other->_y}, other->_radius);
        }

        bool Circle::checkCollisions(Rectangle other) { return CheckCollisionCircleRec({_x, _y}, _radius, other); }

        void Circle::draw3D(Vector3 rotationAxis, float rotationAngle)
        {
            DrawCircle3D({_x, _y, _z}, _radius, rotationAxis, rotationAngle, _color);
        }

        void Circle::setPosition(float x, float y, float z)
        {
            _x = x;
            _y = y;
            _z = z;
        }

        void Circle::setRadius(float radius) { _radius = radius; }

        void Circle::setColor(Color color) { _color = color; }

        Vector3 Circle::getPosition() { return {_x, _y, _z}; }

        float Circle::getRadius() { return _radius; }

        Color Circle::getColor() { return _color; }
    } // namespace shapes

} // namespace raylib
