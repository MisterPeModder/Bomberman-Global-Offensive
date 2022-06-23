/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Rectangle
*/

#include "Rectangle.hpp"
#include "raylib/core/Vector3.hpp"

namespace raylib
{
    namespace shapes
    {
        Rectangle::Rectangle(raylib::core::Vector2f pos, raylib::core::Vector2f size, raylib::core::Color color)
        {
            setPosition(pos);
            setColor(color);
            _size = size;
        }

        Rectangle::Rectangle(::Rectangle rec)
        {
            _position.x = rec.x;
            _position.y = rec.y;
            _size.x = rec.height;
            _size.y = rec.width;
            _color = raylib::core::Color::DEFAULT_COLOR;
        }

        Rectangle::Rectangle(const Rectangle &other)
        {
            _position = other._position;
            _size = other._size;
            _color = other._color;
        }

        Rectangle::~Rectangle() {}

        ::Rectangle Rectangle::getRaylibRectangle() const { return {_position.x, _position.y, _size.x, _size.y}; }

        void Rectangle::draw() const { DrawRectangleRec(this->getRaylibRectangle(), _color.asRaylib()); }

        void Rectangle::draw(raylib::core::Vector2f position, raylib::core::Vector2f size, raylib::core::Color color)
        {
            DrawRectangleV(position.asRaylib(), size.asRaylib(), color.asRaylib());
        }

        void Rectangle::drawLines() const
        {
            DrawRectangleLines(_position.x, _position.y, _size.x, _size.y, _color.asRaylib());
        }

        void Rectangle::drawLines(float lineThick) const
        {
            DrawRectangleLinesEx(this->getRaylibRectangle(), lineThick, _color.asRaylib());
        }

        void Rectangle::drawLines(
            raylib::core::Vector2f position, raylib::core::Vector2f size, float lineThick, raylib::core::Color color)
        {
            DrawRectangleLinesEx({position.x, position.y, size.x, size.y}, lineThick, color.asRaylib());
        }

        void Rectangle::drawRounded(float roundness, float segments) const
        {
            DrawRectangleRounded(this->getRaylibRectangle(), roundness, segments, _color.asRaylib());
        }

        void Rectangle::drawRoundedLines(float roundness, float segments, float lineThick) const
        {
            DrawRectangleRoundedLines(this->getRaylibRectangle(), roundness, segments, lineThick, _color.asRaylib());
        }

        bool Rectangle::checkCollision(Rectangle &other) const
        {
            return CheckCollisionRecs(this->getRaylibRectangle(), other.getRaylibRectangle());
        }

        Rectangle Rectangle::getCollision(Rectangle &other) const
        {
            return GetCollisionRec(this->getRaylibRectangle(), other.getRaylibRectangle());
        }

    } // namespace shapes
} // namespace raylib
