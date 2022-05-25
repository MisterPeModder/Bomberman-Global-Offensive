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
        /// The Vector2 class (compatible with the raylib Vector2)
        class Vector2 {
          public:
            /// Constructor of the vector
            ///
            /// @param x the X axis value of the vector
            /// @param y the Y axis value of the vector
            Vector2(float x = 0.f, float y = 0.f);

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

            /// Get the X axis value of the vector
            ///
            /// @return the X axis value of the vector
            constexpr float getX() const { return _x; }

            /// Set the X acis value of the vector
            ///
            /// @param x the new X axis value of the vector
            constexpr void setX(float x) { _x = x; }

            /// Get the Y axis value of the vector
            ///
            /// @return the Y axis value of the vector
            constexpr float getY() const { return _y; }

            /// Set the Y acis value of the vector
            ///
            /// @param y the new Y axis value of the vector
            constexpr void setY(float y) { _y = y; }

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
            constexpr ::Vector2 asRaylib() const { return {_x, _y}; }

          private:
            float _x;
            float _y;
        };
    } // namespace core
} // namespace raylib

#endif /* RAYLIB_CORE_VECTOR2_HPP_ */
