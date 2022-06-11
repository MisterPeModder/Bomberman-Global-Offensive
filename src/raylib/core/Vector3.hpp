/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Vector3
*/

#ifndef RAYLIB_CORE_VECTOR3_HPP_
#define RAYLIB_CORE_VECTOR3_HPP_

#include "Vector2.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace core
    {
        /// The Vector3 struct (compatible with the raylib Vector3)
        template <typename T = float>
        requires std::is_arithmetic_v<T>
        struct Vector3 {
            /// Constructor of the vector
            ///
            /// @param xParam the X axis value of the vector
            /// @param yParam the Y axis value of the vector
            /// @param zParam the Z axis value of the vector
            constexpr Vector3(T xParam = 0.f, T yParam = 0.f, T zParam = 0.f) : x(xParam), y(yParam), z(zParam) {}

            /// Constructor of the vector using integers
            ///
            /// @param xParam the X axis value of the vector
            /// @param yParam the Y axis value of the vector
            /// @param zParam the Z axis value of the vector
            Vector3(int xParam, int yParam, int zParam);

            /// Constructor of the 3d vector from a 2d vector
            ///
            /// @param vector the 2d vector to convert
            /// @param zParam the Z axis value of the vector
            constexpr Vector3(const Vector2<T> &vector, T zParam = 0.f) : x(vector.x), y(vector.y), z(zParam) {}

            /// The copy constructor
            ///
            /// @param vector the vector to copy
            constexpr Vector3(const Vector3 &vector) = default;

            /// Construct the vector from another type of vector.
            ///
            /// @tparam U type of the other vector.
            /// @param vector vector to convert.
            template <typename U>
            constexpr explicit Vector3(const Vector3<U> &vector)
                : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(static_cast<T>(vector.z))
            {
            }

            /// The copy constructor with vector 3 of raylib
            ///
            /// @param vector the vector to copy
            constexpr Vector3(::Vector3 vector)
                : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(static_cast<T>(vector.z))
            {
            }

            /// Destructor
            constexpr ~Vector3() = default;

            /// The Vector3 copy operator
            /// @param vector the Vector3 to copy
            constexpr Vector3 &operator=(const Vector3 &vector) = default;

            /// The Vector3 copy operator
            ///
            /// @param vector the Vector2 to copy
            constexpr Vector3 &operator=(const Vector2<T> &vector)
            {
                x = vector.x;
                y = vector.y;
                return *this;
            }

            /// The Vector3 add operator from a Vector2
            ///
            /// @param vector the Vector3 to add
            constexpr Vector3 operator+(const Vector3 &vector) const
            {
                return {x + vector.x, y + vector.y, z + vector.z};
            }

            /// The Vector3 assignment add operator
            ///
            /// @param vector the Vector3 to assignment add
            constexpr Vector3 &operator+=(const Vector3 &vector)
            {
                x += vector.x;
                y += vector.y;
                z += vector.z;
                return *this;
            }

            /// The Vector3 remove operator
            ///
            /// @param vector the Vector3 to remove
            constexpr Vector3 operator-(const Vector3 &vector) const
            {
                return {x - vector.x, y - vector.y, z - vector.z};
            }

            /// The Vector3 assignment remove operator
            ///
            /// @param vector the Vector3 to assignment remove
            constexpr Vector3 &operator-=(const Vector3 &vector)
            {
                x -= vector.x;
                y -= vector.y;
                z -= vector.z;
                return *this;
            }

            /// The Vector3 multiply operator
            ///
            /// @param vector the Vector3 to multiply
            constexpr Vector3 operator*(const Vector3 &vector) const
            {
                return {x * vector.x, y * vector.y, z * vector.z};
            }

            /// The Vector3 assignment multiply operator
            ///
            /// @param vector the Vector3 to assignment multiply
            constexpr Vector3 &operator*=(const Vector3 &vector)
            {
                x *= vector.x;
                y *= vector.y;
                z *= vector.z;
                return *this;
            }

            /// The Vector3 divide operator
            ///
            /// @param vector the Vector3 to divide
            constexpr Vector3 operator/(const Vector3 &vector) const
            {
                return {x / vector.x, y / vector.y, z / vector.z};
            }

            /// The Vector3 assignment divide operator
            ///
            /// @param vector the Vector3 to assignment divide
            constexpr Vector3 &operator/=(const Vector3 &vector)
            {
                x /= vector.x;
                y /= vector.y;
                z /= vector.z;
                return *this;
            }

            /// Gets if the two Vector3 are equals or not
            ///
            /// @param vector The second vector to check
            ///
            /// @return true if the vectors are equal or false otherwise
            constexpr bool operator==(const Vector3 &vector) const
            {
                return x == vector.x && y == vector.y && z == vector.z;
            }

            /// Gets if the two Vector3 are equals or not
            ///
            /// @param vector The second vector to check
            ///
            /// @return true if the vectors are not equal or false otherwise
            constexpr bool operator!=(const Vector3 &vector) const { return !(*this == vector); }

            /// Gets the raylib Vector3
            ///
            /// @return The raylib Vector3
            constexpr ::Vector3 asRaylib() const
            {
                return {static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)};
            }

            T x;
            T y;
            T z;
        };

        using Vector3f = Vector3<float>;
        using Vector3u = Vector3<unsigned int>;
        using Vector3i = Vector3<int>;
    } // namespace core
} // namespace raylib

#endif /* RAYLIB_CORE_VECTOR3_HPP_ */
