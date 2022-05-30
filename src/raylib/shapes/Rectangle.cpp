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
        Rectangle::Rectangle(Vector2 pos, Vector2 size, Color color)
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
            _color = {0, 0, 0, 0};
        }

        Rectangle::Rectangle(Rectangle &other)
        {
            _position = other._position;
            _size = other._size;
            _color = other._color;
        }

        Rectangle::~Rectangle() {}

        ::Rectangle Rectangle::getRaylibRectangle() const { return {_position.x, _position.y, _size.x, _size.y}; }

        void Rectangle::draw() const { DrawRectangleRec(this->getRaylibRectangle(), _color); }

        void Rectangle::drawLines() const { DrawRectangleLines(_position.x, _position.y, _size.x, _size.y, _color); }

        void Rectangle::drawLines(float lineThick) const
        {
            DrawRectangleLinesEx(this->getRaylibRectangle(), lineThick, _color);
        }

        void Rectangle::drawRounded(float roundness, float segments) const
        {
            DrawRectangleRounded(this->getRaylibRectangle(), roundness, segments, _color);
        }

        void Rectangle::drawRoundedLines(float roundness, float segments, float lineThick) const
        {
            DrawRectangleRoundedLines(this->getRaylibRectangle(), roundness, segments, lineThick, _color);
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
