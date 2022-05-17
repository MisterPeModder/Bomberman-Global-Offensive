/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Rectangle
*/

#include "Rectangle.hpp"

namespace raylib
{
    namespace shapes
    {

        Rectangle::Rectangle(float posX, float posY, float width, float height, Color color)
        {
            _position.x = posX;
            _position.y = posY;
            _width = width;
            _height = height;
            _color = color;
        }

        Rectangle::Rectangle(::Rectangle rec)
        {
            _position.x = rec.x;
            _position.y = rec.y;
            _width = rec.width;
            _height = rec.height;
            _color = {0, 0, 0, 0};
        }

        Rectangle::Rectangle(Vector2 pos, float width, float height, Color color)
        {
            _position.x = pos.x;
            _position.y = pos.y;
            _width = width;
            _height = height;
            _color = color;
        }

        Rectangle::~Rectangle() {}

        ::Rectangle Rectangle::C_rectangle() { return {_position.x, _position.y, _width, _height}; }

        void Rectangle::draw() { DrawRectangleRec(this->C_rectangle(), _color); }

        void Rectangle::drawLines(Color color) { DrawRectangleLines(_position.x, _position.y, _width, _height, color); }

        void Rectangle::drawLinesEx(float lineThick, Color color)
        {
            DrawRectangleLinesEx(this->C_rectangle(), lineThick, color);
        }

        void Rectangle::drawRounded(float roundness, float segments, Color color)
        {
            DrawRectangleRounded(this->C_rectangle(), roundness, segments, color);
        }

        void Rectangle::drawRoundedLines(float roundness, float segments, float lineThick, Color color)
        {
            DrawRectangleRoundedLines(this->C_rectangle(), roundness, segments, lineThick, color);
        }

        bool Rectangle::checkCollision(Rectangle other)
        {
            return CheckCollisionRecs(this->C_rectangle(), other.C_rectangle());
        }

        Rectangle Rectangle::getCollision(Rectangle other)
        {
            return GetCollisionRec(this->C_rectangle(), other.C_rectangle());
        }

        Color Rectangle::getColor() { return _color; }

        Vector2 Rectangle::getPosition() { return _position; }

        void Rectangle::setColor(Color color) { _color = color; }

        float Rectangle::getWidth() { return _width; }

        float Rectangle::getHeight() { return _height; }

        void Rectangle::setPosition(Vector2 position)
        {
            _position.x = position.x;
            _position.y = position.y;
        }

        void Rectangle::setSize(float width, float height)
        {
            _width = width;
            _height = height;
        }

    } // namespace shapes
} // namespace raylib
