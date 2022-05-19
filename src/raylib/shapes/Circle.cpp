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
        Circle::Circle(Vector2 pos, float radius, Color color)
        {
            setPosition(pos);
            setColor(color);
            _radius = radius;
        }

        Circle::~Circle() {}

        void Circle::draw() const { DrawCircle(_position.x, _position.y, _radius, _color); }

        void Circle::drawSector(float startAngle, float endAngle, int segments) const
        {
            DrawCircleSector(getPosition2D(), _radius, startAngle, endAngle, segments, _color);
        }

        void Circle::drawSectorLines(float startAngle, float endAngle, int segments) const
        {
            DrawCircleSectorLines(getPosition2D(), _radius, startAngle, endAngle, segments, _color);
        }

        void Circle::drawGradient(Color color1, Color color2) const
        {
            DrawCircleGradient(_position.x, _position.y, _radius, color1, color2);
        }

        void Circle::drawLines() const { DrawCircleLines(_position.x, _position.y, _radius, _color); }

        bool Circle::checkCollisions(const Circle &other) const
        {
            CheckCollisionCircles(getPosition2D(), _radius, other.getPosition2D(), other.getRadius());
        }

        bool Circle::checkCollisions(const Rectangle &other) const
        {
            CheckCollisionCircleRec(getPosition2D(), _radius, other);
        }

        void Circle::draw3D(Vector3 rotationAxis, float rotationAngle) const
        {
            DrawCircle3D(getPosition(), _radius, rotationAxis, rotationAngle, _color);
        }

        void Circle::setRadius(float radius) { _radius = radius; }
    } // namespace shapes

} // namespace raylib
