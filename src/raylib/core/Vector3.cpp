/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Vector3
*/

#include "Vector3.hpp"

namespace raylib
{
    namespace core
    {
        Vector3::Vector3(float xParam, float yParam, float zParam) : x(xParam), y(yParam), z(zParam) {}

        Vector3::Vector3(const Vector2 &vector, float zParam) : x(vector.x), y(vector.y), z(zParam) {}

        Vector3::~Vector3() {}

        Vector3::Vector3(const Vector3 &vector) : x(vector.x), y(vector.y), z(vector.z) {}

        Vector3::Vector3(::Vector3 vector) : x(vector.x), y(vector.y), z(vector.z) {}

        Vector3 &Vector3::operator=(const Vector3 &vector)
        {
            x = vector.x;
            y = vector.y;
            z = vector.z;
            return *this;
        }

        Vector3 &Vector3::operator=(const Vector2 &vector)
        {
            x = vector.x;
            y = vector.y;
            z = 0;
            return *this;
        }

        Vector3 Vector3::operator+(const Vector3 &vector)
        {
            return {this->x + vector.x, this->y + vector.y, this->z + vector.z};
        }

        Vector3 &Vector3::operator+=(const Vector3 &vector)
        {
            this->x += vector.x;
            this->y += vector.y;
            this->z += vector.z;
            return *this;
        }

        Vector3 Vector3::operator-(const Vector3 &vector)
        {
            return {this->x - vector.x, this->y - vector.y, this->z - vector.z};
        }

        Vector3 &Vector3::operator-=(const Vector3 &vector)
        {
            this->x -= vector.x;
            this->y -= vector.y;
            this->z -= vector.z;
            return *this;
        }

        Vector3 Vector3::operator*(const Vector3 &vector)
        {
            return {this->x * vector.x, this->y * vector.y, this->z * vector.z};
        }

        Vector3 &Vector3::operator*=(const Vector3 &vector)
        {
            this->x *= vector.x;
            this->y *= vector.y;
            this->z *= vector.z;
            return *this;
        }

        Vector3 Vector3::operator/(const Vector3 &vector)
        {
            return {this->x / vector.x, this->y + vector.y, this->z + vector.z};
        }

        Vector3 &Vector3::operator/=(const Vector3 &vector)
        {
            this->x /= vector.x;
            this->y /= vector.y;
            this->z /= vector.z;
            return *this;
        }
    } // namespace core
} // namespace raylib
