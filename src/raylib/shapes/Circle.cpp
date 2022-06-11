/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Circle
*/

#include "Circle.hpp"
#include "Rectangle.hpp"

namespace raylib
{
    namespace shapes
    {
        Circle::Circle(raylib::core::Vector2f pos, float radius, raylib::core::Color color)
        {
            setPosition(pos);
            setColor(color);
            _radius = radius;
        }

        Circle::~Circle() {}

        void Circle::draw() const { DrawCircle(_position.x, _position.y, _radius, _color.asRaylib()); }

        void Circle::drawSector(float startAngle, float endAngle, int segments) const
        {
            DrawCircleSector(getPosition2D().asRaylib(), _radius, startAngle, endAngle, segments, _color.asRaylib());
        }

        void Circle::drawSectorLines(float startAngle, float endAngle, int segments) const
        {
            DrawCircleSectorLines(
                getPosition2D().asRaylib(), _radius, startAngle, endAngle, segments, _color.asRaylib());
        }

        void Circle::drawGradient(raylib::core::Color color1, raylib::core::Color color2) const
        {
            DrawCircleGradient(_position.x, _position.y, _radius, color1.asRaylib(), color2.asRaylib());
        }

        void Circle::drawLines() const { DrawCircleLines(_position.x, _position.y, _radius, _color.asRaylib()); }

        bool Circle::checkCollisions(const Circle &other) const
        {
            return CheckCollisionCircles(
                getPosition2D().asRaylib(), _radius, other.getPosition2D().asRaylib(), other.getRadius());
        }

        bool Circle::checkCollisions(const Rectangle &other) const
        {
            return CheckCollisionCircleRec(getPosition2D().asRaylib(), _radius, other.getRaylibRectangle());
        }

        void Circle::draw3D(raylib::core::Vector3f rotationAxis, float rotationAngle) const
        {
            DrawCircle3D(getPosition().asRaylib(), _radius, rotationAxis.asRaylib(), rotationAngle, _color.asRaylib());
        }

        void Circle::setRadius(float radius) { _radius = radius; }
    } // namespace shapes

} // namespace raylib
