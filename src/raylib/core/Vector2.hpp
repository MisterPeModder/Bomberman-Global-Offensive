/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Vector2
*/

#ifndef RAYLIB_CORE_VECTOR2_HPP_
#define RAYLIB_CORE_VECTOR2_HPP_

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace core
    {
        /// The Vector2 struct (compatible with the raylib Vector2)
        struct Vector2 {
            /// Constructor of the vector
            ///
            /// @param xParam the X axis value of the vector
            /// @param yParam the Y axis value of the vector
            Vector2(float xParam = 0.f, float yParam = 0.f);

            /// The copy constructor
            ///
            /// @param vector the vector to copy
            Vector2(const Vector2 &vector);

            /// The copy constructor with vector 2 of raylib
            ///
            /// @param vector the vector to copy
            Vector2(::Vector2 vector);

            /// Destructor
            ~Vector2();

            /// The Vector2 copy operator
            ///
            /// @param vector the Vector2 to copy
            Vector2 &operator=(const Vector2 &vector);

            /// The Vector2 add operator
            ///
            /// @param vector the Vector2 to add
            Vector2 operator+(const Vector2 &vector);

            /// The Vector2 assignment add operator
            ///
            /// @param vector the Vector2 to assignment add
            Vector2 &operator+=(const Vector2 &vector);

            /// The Vector2 remove operator
            ///
            /// @param vector the Vector2 to remove
            Vector2 operator-(const Vector2 &vector);

            /// The Vector2 assignment remove operator
            ///
            /// @param vector the Vector2 to assignment remove
            Vector2 &operator-=(const Vector2 &vector);

            /// The Vector2 multiply operator
            ///
            /// @param vector the Vector2 to multiply
            Vector2 operator*(const Vector2 &vector);

            /// The Vector2 assignment multiply operator
            ///
            /// @param vector the Vector2 to assignment multiply
            Vector2 &operator*=(const Vector2 &vector);

            /// The Vector2 divide operator
            ///
            /// @param vector the Vector2 to divide
            Vector2 operator/(const Vector2 &vector);

            /// The Vector2 assignment divide operator
            ///
            /// @param vector the Vector2 to assignment divide
            Vector2 &operator/=(const Vector2 &vector);

            /// Gets the raylib Vector2
            ///
            /// @return The raylib Vector2
            constexpr ::Vector2 asRaylib() const { return {x, y}; }

            /// Gets if the two Vector2 are equals or not
            ///
            /// @param second The second vector to check
            ///
            /// @return true if the vectors are equal or false otherwise
            bool operator==(const Vector2 &second) const;

            /// Gets if the two Vector2 are equals or not
            ///
            /// @param second The second vector to check
            ///
            /// @return true if the vectors are not equal or false otherwise
            bool operator!=(const Vector2 &second) const;

            float x;
            float y;
        };
    } // namespace core
} // namespace raylib

#endif /* RAYLIB_CORE_VECTOR2_HPP_ */
