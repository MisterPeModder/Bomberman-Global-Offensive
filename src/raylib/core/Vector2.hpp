/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Vector2
*/

#ifndef RAYLIB_CORE_VECTOR2_HPP_
#define RAYLIB_CORE_VECTOR2_HPP_

#include <type_traits>

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace core
    {
        /// The Vector2 struct (compatible with the raylib Vector2)
        template <typename T = float>
        requires std::is_arithmetic_v<T>
        struct Vector2 {
            /// Constructor of the vector
            ///
            /// @param xParam the X axis value of the vector
            /// @param yParam the Y axis value of the vector
            constexpr Vector2(T xParam = 0, T yParam = 0) : x(xParam), y(yParam){};

            /// The copy constructor
            ///
            /// @param vector the vector to copy
            constexpr Vector2(const Vector2 &vector) = default;

            /// The copy constructor with vector 2 of raylib
            ///
            /// @param vector the vector to copy
            constexpr Vector2(::Vector2 vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)) {}

            /// Construct the vector from another type of vector.
            ///
            /// @tparam U type of the other vector.
            /// @param vector vector to convert.
            template <typename U>
            constexpr explicit Vector2(const Vector2<U> &vector)
                : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y))
            {
            }

            /// Destructor
            ~Vector2() = default;

            /// The Vector2 copy operator
            ///
            /// @param vector the Vector2 to copy
            constexpr Vector2 &operator=(const Vector2 &vector) = default;

            /// The Vector2 add operator
            ///
            /// @param vector the Vector2 to add
            constexpr Vector2 operator+(const Vector2 &vector) const { return {x + vector.x, y + vector.y}; };

            /// The Vector2 assignment add operator
            ///
            /// @param vector the Vector2 to assignment add
            constexpr Vector2 &operator+=(const Vector2 &vector)
            {
                x += vector.x;
                y += vector.y;
                return *this;
            };

            /// The Vector2 remove operator
            ///
            /// @param vector the Vector2 to remove
            constexpr Vector2 operator-(const Vector2 &vector) const { return {x - vector.x, y - vector.y}; };

            /// The Vector2 assignment remove operator
            ///
            /// @param vector the Vector2 to assignment remove
            constexpr Vector2 &operator-=(const Vector2 &vector)
            {
                x -= vector.x;
                y -= vector.y;
                return *this;
            };

            /// The Vector2 multiply operator
            ///
            /// @param vector the Vector2 to multiply
            constexpr Vector2 operator*(const Vector2 &vector) const { return {x * vector.x, y * vector.y}; };

            /// The Vector2 assignment multiply operator
            ///
            /// @param vector the Vector2 to assignment multiply
            constexpr Vector2 &operator*=(const Vector2 &vector)
            {
                x *= vector.x;
                y *= vector.y;
                return *this;
            };

            /// The Vector2 divide operator
            ///
            /// @param vector the Vector2 to divide
            constexpr Vector2 operator/(const Vector2 &vector) const { return {x / vector.x, y / vector.y}; };

            /// The Vector2 assignment divide operator
            ///
            /// @param vector the Vector2 to assignment divide
            constexpr Vector2 &operator/=(const Vector2 &vector)
            {
                x /= vector.x;
                y /= vector.y;
                return *this;
            };

            /// Gets the raylib Vector2
            ///
            /// @return The raylib Vector2
            constexpr ::Vector2 asRaylib() const { return {static_cast<float>(x), static_cast<float>(y)}; }

            /// Gets if the two Vector2 are equals or not
            ///
            /// @param second The second vector to check
            ///
            /// @return true if the vectors are equal or false otherwise
            constexpr bool operator==(const Vector2 &vector) const { return x == vector.x && y == vector.y; }

            /// Gets if the two Vector2 are equals or not
            ///
            /// @param second The second vector to check
            ///
            /// @return true if the vectors are not equal or false otherwise
            constexpr bool operator!=(const Vector2 &vector) const { return !(*this == vector); }

            T x;
            T y;
        };

        using Vector2f = Vector2<float>;
    } // namespace core
} // namespace raylib

#endif /* RAYLIB_CORE_VECTOR2_HPP_ */
