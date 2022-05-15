/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Rectangle
*/

#include "Rectangle.hpp"

raylib::Shapes::Rectangle::Rectangle(int posX, int posY, int width, int height)
{
    _position.x = posX;
    _position.y = posY;
    _width = width;
    _height = height;
}

raylib::Shapes::Rectangle::Rectangle(Vector2 pos, int width, int height)
{
    _position.x = pos._x;
    _position.y = pos._y;
    _width = width;
    _height = height;
}

raylib::Shapes::Rectangle::~Rectangle()
{

}

void raylib::Shapes::Rectangle::drawRectangle(int posX, int posY, int width, int height, Color color)
{
    DrawRectangle(posX, posY, width, height, color);
}

void raylib::Shapes::Rectangle::drawRectangleV(Vector2 position, Vector2 size, Color color)
{
    DrawRectangleV(position, size, color);
}

void raylib::Shapes::Rectangle::drawRectangleRec(Rectangle rec, Color color)
{
    DrawRectangleRec(rec, color);
}

void raylib::Shapes::Rectangle::drawRectangleLines(int posX, int posY, int width, int height, Color color)
{
    DrawRectangleLines(posX, posY, width, height, color);
}

void raylib::Shapes::Rectangle::drawRectangleLines(Vector2 pos, int width, int height, Color color)
{
    DrawRectangleLines(pos.x, pos.y, width, height, color);
}

void raylib::Shapes::Rectangle::drawRectangleLinesEx(Rectangle rec, int lineThick, Color color)
{
    DrawRectangleLinesEx(rec, lineThick, color);
}

void raylib::Shapes::Rectangle::drawRectangleRounded(Rectangle rec, float roundness, int segments, Color color)
{
    DrawRectangleRounded(rec, roundness, segments, color);
}

void raylib::Shapes::Rectangle::drawRectangleRoundedLines(Rectangle rec, float roundness, int segments, int lineThick, Color color)
{
    DrawRectangleRoundedLines(rec, roundness, segments, lineThick, color);
}

bool raylib::Shapes::Rectangle::checkCollisionRecs(Rectangle rec1, Rectangle rec2)
{
    return CheckCollisionRecs(rec1, rec2);
}

raylib::Shapes::Rectangle getCollisionRec(Rectangle rec1, Rectangle rec2)
{
    return GetCollisionRec(rec1, rec2);
}