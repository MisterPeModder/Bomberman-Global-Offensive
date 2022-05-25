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
        Vector3::Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) {}

        Vector3::Vector3(const Vector2 &vector, float z) : _x(vector.getX()), _y(vector.getY()), _z(z) {}

        Vector3::~Vector3() {}

        Vector3::Vector3(const Vector3 &vector) : _x(vector._x), _y(vector._y), _z(vector._z) {}

        Vector3::Vector3(::Vector3 vector) : _x(vector.x), _y(vector.y), _z(vector.z) {}

        Vector3 &Vector3::operator=(const Vector3 &vector)
        {
            _x = vector.getX();
            _y = vector.getY();
            _z = vector.getZ();
            return *this;
        }

        Vector3 &Vector3::operator=(const Vector2 &vector)
        {
            _x = vector.getX();
            _y = vector.getY();
            _z = 0;
            return *this;
        }

        Vector3 Vector3::operator+(const Vector3 &vector)
        {
            return {this->_x + vector._x, this->_y + vector._y, this->_z + vector._z};
        }

        Vector3 &Vector3::operator+=(const Vector3 &vector)
        {
            this->_x += vector.getX();
            this->_y += vector.getY();
            this->_z += vector.getZ();
            return *this;
        }

        Vector3 Vector3::operator-(const Vector3 &vector)
        {
            return {this->_x - vector._x, this->_y - vector._y, this->_z - vector._z};
        }

        Vector3 &Vector3::operator-=(const Vector3 &vector)
        {
            this->_x -= vector._x;
            this->_y -= vector._y;
            this->_z -= vector._z;
            return *this;
        }

        Vector3 Vector3::operator*(const Vector3 &vector)
        {
            return {this->_x * vector._x, this->_y * vector._y, this->_z * vector._z};
        }

        Vector3 &Vector3::operator*=(const Vector3 &vector)
        {
            this->_x *= vector._x;
            this->_y *= vector._y;
            this->_z *= vector._z;
            return *this;
        }

        Vector3 Vector3::operator/(const Vector3 &vector)
        {
            return {this->_x / vector._x, this->_y + vector._y, this->_z + vector._z};
        }

        Vector3 &Vector3::operator/=(const Vector3 &vector)
        {
            this->_x /= vector._x;
            this->_y /= vector._y;
            this->_z /= vector._z;
            return *this;
        }
    } // namespace core
} // namespace raylib
