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
            _position.x = x;
            _position.y = y;
            _position.z = z;
            _radius = radius;
            _color = color;
        }

        Circle::Circle(Vector3 position, float radius, Color color)
        {
            _position.x = position.x;
            _position.y = position.y;
            _position.z = position.z;
            _radius = radius;
            _color = color;
        }

        void Circle::draw() { DrawCircle(_position.x, _position.y, _radius, _color); }

        void Circle::drawSector(float startAngle, float endAngle, float segments, Color color)
        {
            DrawCircleSector({_position.x, _position.y}, _radius, startAngle, endAngle, segments, color);
        }

        void Circle::drawSectorLines(float startAngle, float endAngle, float segments, Color color)
        {
            DrawCircleSectorLines({_position.x, _position.y}, _radius, startAngle, endAngle, segments, color);
        }

        void Circle::drawGradient(Color color1, Color color2) { DrawCircleGradient(_position.x, _position.y, _radius, color1, color2); }

        void Circle::drawLines(Color color) { DrawCircleLines(_position.x, _position.y, _radius, color); }

        bool Circle::checkCollisions(Circle *other)
        {
            return CheckCollisionCircles({_position.x, _position.y}, _radius, {other->_position.x, other->_position.y}, other->_radius);
        }

        bool Circle::checkCollisions(Rectangle other) { return CheckCollisionCircleRec({_position.x, _position.y}, _radius, other); }

        void Circle::draw3D(Vector3 rotationAxis, float rotationAngle)
        {
            DrawCircle3D(_position, _radius, rotationAxis, rotationAngle, _color);
        }

        void Circle::setPosition(float x, float y, float z)
        {
            _position.x = x;
            _position.y = y;
            _position.z = z;
        }

        void Circle::setPosition(Vector3 position)
        {
            _position.x = position.x;
            _position.y = position.y;
            _position.z = position.z;
        }

        void Circle::setRadius(float radius) { _radius = radius; }

        void Circle::setColor(Color color) { _color = color; }

        Vector3 Circle::getPosition() { return _position; }

        float Circle::getRadius() { return _radius; }

        Color Circle::getColor() { return _color; }
    } // namespace shapes

} // namespace raylib
