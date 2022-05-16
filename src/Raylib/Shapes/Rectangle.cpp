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

        Rectangle::Rectangle(float posX, float posY, float width, float height)
        {
            _position.x = posX;
            _position.y = posY;
            _width = width;
            _height = height;
        }

        Rectangle::Rectangle(::Rectangle rec)
        {
            _position.x = rec.x;
            _position.y = rec.y;
            _width = rec.width;
            _height = rec.height;
        }

        Rectangle::Rectangle(Vector2 pos, float width, float height)
        {
            _position.x = pos.x;
            _position.y = pos.y;
            _width = width;
            _height = height;
        }

        Rectangle::~Rectangle() {}

        ::Rectangle Rectangle::C_rectangle() { return {_position.x, _position.y, _width, _height}; }

        void Rectangle::drawRectangle(float posX, float posY, float width, float height, Color color)
        {
            DrawRectangle(posX, posY, width, height, color);
        }

        void Rectangle::drawRectangleV(Vector2 position, Vector2 size, Color color)
        {
            DrawRectangleV(position, size, color);
        }

        void Rectangle::drawRectangleRec(Rectangle rec, Color color) { DrawRectangleRec(rec.C_rectangle(), color); }

        void Rectangle::drawRectangleLines(float posX, float posY, float width, float height, Color color)
        {
            DrawRectangleLines(posX, posY, width, height, color);
        }

        void Rectangle::drawRectangleLines(Vector2 pos, float width, float height, Color color)
        {
            DrawRectangleLines(pos.x, pos.y, width, height, color);
        }

        void Rectangle::drawRectangleLinesEx(Rectangle rec, float lineThick, Color color)
        {
            DrawRectangleLinesEx(rec.C_rectangle(), lineThick, color);
        }

        void Rectangle::drawRectangleRounded(Rectangle rec, float roundness, float segments, Color color)
        {
            DrawRectangleRounded(rec.C_rectangle(), roundness, segments, color);
        }

        void Rectangle::drawRectangleRoundedLines(
            Rectangle rec, float roundness, float segments, float lineThick, Color color)
        {
            DrawRectangleRoundedLines(rec.C_rectangle(), roundness, segments, lineThick, color);
        }

        bool Rectangle::checkCollisionRecs(Rectangle rec1, Rectangle rec2)
        {
            return CheckCollisionRecs(rec1.C_rectangle(), rec2.C_rectangle());
        }

        Rectangle getCollisionRec(Rectangle rec1, Rectangle rec2)
        {
            return GetCollisionRec(rec1.C_rectangle(), rec2.C_rectangle());
        }
    } // namespace shapes

} // namespace raylib
