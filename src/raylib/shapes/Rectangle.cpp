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
            _position = {pos.x, pos.y, 0};
            _size = {size.x, size.y, 0};
            _color = color;
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

        void Rectangle::draw() { DrawRectangleRec(this->getRaylibRectangle(), _color); }

        void Rectangle::drawLines(Color color) { DrawRectangleLines(_position.x, _position.y, _size.x, _size.y, color); }

        void Rectangle::drawLinesEx(float lineThick, Color color)
        {
            DrawRectangleLinesEx(this->getRaylibRectangle(), lineThick, color);
        }

        void Rectangle::drawRounded(float roundness, float segments, Color color)
        {
            DrawRectangleRounded(this->getRaylibRectangle(), roundness, segments, color);
        }

        void Rectangle::drawRoundedLines(float roundness, float segments, float lineThick, Color color)
        {
            DrawRectangleRoundedLines(this->getRaylibRectangle(), roundness, segments, lineThick, color);
        }

        bool Rectangle::checkCollision(Rectangle other)
        {
            return CheckCollisionRecs(this->getRaylibRectangle(), other.getRaylibRectangle());
        }

        Rectangle Rectangle::getCollision(Rectangle other)
        {
            return GetCollisionRec(this->getRaylibRectangle(), other.getRaylibRectangle());
        }

    } // namespace shapes
} // namespace raylib
