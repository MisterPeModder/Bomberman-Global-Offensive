/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Vector2
*/

#include "Vector2.hpp"

raylib::Core::Vector2::Vector2(float x, float y)
 : _x(x), _y(y)
{
}

raylib::Core::Vector2::~Vector2()
{
}

raylib::Core::Vector2::Vector2(const Vector2& vector)
 : _x(vector._x), _y(vector._y)
{
}

raylib::Core::Vector2 &raylib::Core::Vector2::operator=(const Vector2& vector)
{
    _x = vector._x;
    _y = vector._y;
    return *this;
}

raylib::Core::Vector2 raylib::Core::Vector2::operator+(const Vector2& vector)
{
    return {this->_x + vector._x, this->_y + vector._y};
}

raylib::Core::Vector2 &raylib::Core::Vector2::operator+=(const Vector2& vector)
{
    this->_x += vector._x;
    this->_y += vector._y;
    return *this;
}

raylib::Core::Vector2 raylib::Core::Vector2::operator-(const Vector2& vector)
{
    return {this->_x - vector._x, this->_y - vector._y};
}

raylib::Core::Vector2 &raylib::Core::Vector2::operator-=(const Vector2& vector)
{
    this->_x -= vector._x;
    this->_y -= vector._y;
    return *this;
}

raylib::Core::Vector2 raylib::Core::Vector2::operator*(const Vector2& vector)
{
    return {this->_x * vector._x, this->_y * vector._y};
}

raylib::Core::Vector2 &raylib::Core::Vector2::operator*=(const Vector2& vector)
{
    this->_x *= vector._x;
    this->_y *= vector._y;
    return *this;
}

raylib::Core::Vector2 raylib::Core::Vector2::operator/(const Vector2& vector)
{
    return {this->_x / vector._x, this->_y + vector._y};
}

raylib::Core::Vector2 &raylib::Core::Vector2::operator/=(const Vector2& vector)
{
    this->_x /= vector._x;
    this->_y /= vector._y;
    return *this;
}
