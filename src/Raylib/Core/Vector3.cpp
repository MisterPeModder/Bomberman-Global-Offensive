/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Vector3
*/

#include "Vector3.hpp"

raylib::Core::Vector3::Vector3(float x, float y, float z)
 : _x(x), _y(y), _z(z)
{
}

raylib::Core::Vector3::Vector3(const Vector2& vector, float z)
 : _x(vector.getX()), _y(vector.getY()), _z(z)
{
}

raylib::Core::Vector3::~Vector3()
{
}

raylib::Core::Vector3::Vector3(const Vector3& vector)
 : _x(vector._x), _y(vector._y), _z(vector._z)
{
}

raylib::Core::Vector3::Vector3(::Vector3 vector)
 : _x(vector.x), _y(vector.y), _z(vector.z)
{
}

raylib::Core::Vector3 &raylib::Core::Vector3::operator=(const Vector3& vector)
{
    _x = vector._x;
    _y = vector._y;
    _z = vector._z;
    return *this;
}

raylib::Core::Vector3 raylib::Core::Vector3::operator+(const Vector3& vector)
{
    return {this->_x + vector._x, this->_y + vector._y, this->_z + vector._z};
}

raylib::Core::Vector3 &raylib::Core::Vector3::operator+=(const Vector3& vector)
{
    this->_x += vector._x;
    this->_y += vector._y;
    this->_z += vector._z;
    return *this;
}

raylib::Core::Vector3 raylib::Core::Vector3::operator-(const Vector3& vector)
{
    return {this->_x - vector._x, this->_y - vector._y, this->_z - vector._z};
}

raylib::Core::Vector3 &raylib::Core::Vector3::operator-=(const Vector3& vector)
{
    this->_x -= vector._x;
    this->_y -= vector._y;
    this->_z -= vector._z;
    return *this;
}

raylib::Core::Vector3 raylib::Core::Vector3::operator*(const Vector3& vector)
{
    return {this->_x * vector._x, this->_y * vector._y, this->_z * vector._z};
}

raylib::Core::Vector3 &raylib::Core::Vector3::operator*=(const Vector3& vector)
{
    this->_x *= vector._x;
    this->_y *= vector._y;
    this->_z *= vector._z;
    return *this;
}

raylib::Core::Vector3 raylib::Core::Vector3::operator/(const Vector3& vector)
{
    return {this->_x / vector._x, this->_y + vector._y, this->_z + vector._z};
}

raylib::Core::Vector3 &raylib::Core::Vector3::operator/=(const Vector3& vector)
{
    this->_x /= vector._x;
    this->_y /= vector._y;
    this->_z /= vector._z;
    return *this;
}
