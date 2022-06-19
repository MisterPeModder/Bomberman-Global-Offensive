/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Vector4
*/

#ifndef RAYLIB_CORE_VECTOR4_HPP_
#define RAYLIB_CORE_VECTOR4_HPP_

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace core
    {
        /// The Vector4 struct (compatible with the raylib Vector4)
        template <typename T = float>
        requires std::is_arithmetic_v<T>
        struct Vector4 {
            /// Constructor of the vector
            ///
            /// @param xParam the X axis value of the vector
            /// @param yParam the Y axis value of the vector
            /// @param zParam the Z axis value of the vector
            /// @param zParam the W axis value of the vector
            constexpr Vector4(T xParam = 0.f, T yParam = 0.f, T zParam = 0.f, T wParam = 0.f)
                : x(xParam), y(yParam), z(zParam), w(wParam)
            {
            }

            /// The copy constructor
            ///
            /// @param vector the vector to copy
            constexpr Vector4(const Vector4 &vector) = default;

            /// Construct the vector from another type of vector.
            ///
            /// @tparam U type of the other vector.
            /// @param vector vector to convert.
            template <typename U>
            constexpr explicit Vector4(const Vector4<U> &vector)
                : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(static_cast<T>(vector.z)),
                  w(static_cast<T>(vector.w))
            {
            }

            /// The copy constructor with vector 4 of raylib
            ///
            /// @param vector the vector to copy
            constexpr Vector4(::Vector4 vector)
                : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(static_cast<T>(vector.z)),
                  w(static_cast<T>(vector.w))
            {
            }

            /// Destructor
            constexpr ~Vector4() = default;

            /// The Vector4 copy operator
            /// @param vector the Vector4 to copy
            constexpr Vector4 &operator=(const Vector4 &vector) = default;

            /// The Vector4 add operator from a Vector2
            ///
            /// @param vector the Vector4 to add
            constexpr Vector4 operator+(const Vector4 &vector) const
            {
                return {x + vector.x, y + vector.y, z + vector.z, w + vector.w};
            }

            /// The Vector4 assignment add operator
            ///
            /// @param vector the Vector4 to assignment add
            constexpr Vector4 &operator+=(const Vector4 &vector)
            {
                x += vector.x;
                y += vector.y;
                z += vector.z;
                w += vector.w;
                return *this;
            }

            /// The Vector4 remove operator
            ///
            /// @param vector the Vector4 to remove
            constexpr Vector4 operator-(const Vector4 &vector) const
            {
                return {x - vector.x, y - vector.y, z - vector.z, w - vector.w};
            }

            /// The Vector4 assignment remove operator
            ///
            /// @param vector the Vector4 to assignment remove
            constexpr Vector4 &operator-=(const Vector4 &vector)
            {
                x -= vector.x;
                y -= vector.y;
                z -= vector.z;
                w -= vector.w;
                return *this;
            }

            /// The Vector4 multiply operator
            ///
            /// @param vector the Vector4 to multiply
            constexpr Vector4 operator*(const Vector4 &vector) const
            {
                return {x * vector.x, y * vector.y, z * vector.z, w * vector.w};
            }

            /// The Vector4 assignment multiply operator
            ///
            /// @param vector the Vector4 to assignment multiply
            constexpr Vector4 &operator*=(const Vector4 &vector)
            {
                x *= vector.x;
                y *= vector.y;
                z *= vector.z;
                w *= vector.w;
                return *this;
            }

            /// The Vector4 divide operator
            ///
            /// @param vector the Vector4 to divide
            constexpr Vector4 operator/(const Vector4 &vector) const
            {
                return {x / vector.x, y / vector.y, z / vector.z, w / vector.w};
            }

            /// The Vector4 assignment divide operator
            ///
            /// @param vector the Vector4 to assignment divide
            constexpr Vector4 &operator/=(const Vector4 &vector)
            {
                x /= vector.x;
                y /= vector.y;
                z /= vector.z;
                w /= vector.w;
                return *this;
            }

            /// Gets if the two Vector4 are equals or not
            ///
            /// @param vector The second vector to check
            ///
            /// @return true if the vectors are equal or false otherwise
            constexpr bool operator==(const Vector4 &vector) const
            {
                return x == vector.x && y == vector.y && z == vector.z && w == vector.w;
            }

            /// Gets if the two Vector4 are equals or not
            ///
            /// @param vector The second vector to check
            ///
            /// @return true if the vectors are not equal or false otherwise
            constexpr bool operator!=(const Vector4 &vector) const { return !(*this == vector); }

            /// Gets the raylib Vector4
            ///
            /// @return The raylib Vector4
            constexpr ::Vector4 asRaylib() const
            {
                return {static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w)};
            }

            T x;
            T y;
            T z;
            T w;
        };

        using Vector4f = Vector4<float>;
        using Vector4u = Vector4<unsigned int>;
        using Vector4i = Vector4<int>;
    } // namespace core
} // namespace raylib

#endif /* RAYLIB_CORE_VECTOR4_HPP_ */
