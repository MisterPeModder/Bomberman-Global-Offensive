/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Vector2
*/

#include "Vector2.hpp"

namespace raylib
{
    namespace core
    {

        Vector2::Vector2(float x, float y) : _x(x), _y(y) {}

        Vector2::~Vector2() {}

        Vector2::Vector2(const Vector2 &vector) : _x(vector._x), _y(vector._y) {}

        Vector2::Vector2(::Vector2 vector) : _x(vector.x), _y(vector.y) {}

        Vector2 &Vector2::operator=(const Vector2 &vector)
        {
            _x = vector._x;
            _y = vector._y;
            return *this;
        }

        Vector2 Vector2::operator+(const Vector2 &vector) { return {this->_x + vector._x, this->_y + vector._y}; }

        Vector2 &Vector2::operator+=(const Vector2 &vector)
        {
            this->_x += vector._x;
            this->_y += vector._y;
            return *this;
        }

        Vector2 Vector2::operator-(const Vector2 &vector) { return {this->_x - vector._x, this->_y - vector._y}; }

        Vector2 &Vector2::operator-=(const Vector2 &vector)
        {
            this->_x -= vector._x;
            this->_y -= vector._y;
            return *this;
        }

        Vector2 Vector2::operator*(const Vector2 &vector) { return {this->_x * vector._x, this->_y * vector._y}; }

        Vector2 &Vector2::operator*=(const Vector2 &vector)
        {
            this->_x *= vector._x;
            this->_y *= vector._y;
            return *this;
        }

        Vector2 Vector2::operator/(const Vector2 &vector) { return {this->_x / vector._x, this->_y + vector._y}; }

        Vector2 &Vector2::operator/=(const Vector2 &vector)
        {
            this->_x /= vector._x;
            this->_y /= vector._y;
            return *this;
        }
    } // namespace core
} // namespace raylib
