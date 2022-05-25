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
        Vector2::Vector2(float xParam, float yParam) : x(xParam), y(yParam) {}

        Vector2::~Vector2() {}

        Vector2::Vector2(const Vector2 &vector) : x(vector.x), y(vector.y) {}

        Vector2::Vector2(::Vector2 vector) : x(vector.x), y(vector.y) {}

        Vector2 &Vector2::operator=(const Vector2 &vector)
        {
            x = vector.x;
            y = vector.y;
            return *this;
        }

        Vector2 Vector2::operator+(const Vector2 &vector) { return {this->x + vector.x, this->y + vector.y}; }

        Vector2 &Vector2::operator+=(const Vector2 &vector)
        {
            this->x += vector.x;
            this->y += vector.y;
            return *this;
        }

        Vector2 Vector2::operator-(const Vector2 &vector) { return {this->x - vector.x, this->y - vector.y}; }

        Vector2 &Vector2::operator-=(const Vector2 &vector)
        {
            this->x -= vector.x;
            this->y -= vector.y;
            return *this;
        }

        Vector2 Vector2::operator*(const Vector2 &vector) { return {this->x * vector.x, this->y * vector.y}; }

        Vector2 &Vector2::operator*=(const Vector2 &vector)
        {
            this->x *= vector.x;
            this->y *= vector.y;
            return *this;
        }

        Vector2 Vector2::operator/(const Vector2 &vector) { return {this->x / vector.x, this->y + vector.y}; }

        Vector2 &Vector2::operator/=(const Vector2 &vector)
        {
            this->x /= vector.x;
            this->y /= vector.y;
            return *this;
        }
    } // namespace core
} // namespace raylib
