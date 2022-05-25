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
        struct Vector3 {
            /// Constructor of the vector
            ///
            /// @param xParam the X axis value of the vector
            /// @param yParam the Y axis value of the vector
            /// @param zParam the Z axis value of the vector
            Vector3(float xParam = 0.f, float yParam = 0.f, float zParam = 0.f);

            /// Constructor of the 3d vector from a 2d vector
            ///
            /// @param vector the 2d vector to convert
            /// @param zParam the Z axis value of the vector
            Vector3(const Vector2 &vector, float zParam = 0.f);

            /// The copy constructor
            ///
            /// @param vector the vector to copy
            Vector3(const Vector3 &vector);

            /// The copy constructor with vector 3 of raylib
            ///
            /// @param vector the vector to copy
            Vector3(::Vector3 vector);

            /// Destructor
            ~Vector3();

            /// The Vector3 copy operator
            /// @param vector the Vector3 to copy
            Vector3 &operator=(const Vector3 &vector);

            /// The Vector3 copy operator
            ///
            /// @param vector the Vector2 to copy
            Vector3 &operator=(const Vector2 &vector);

            /// The Vector3 add operator from a Vector2
            ///
            /// @param vector the Vector3 to add
            Vector3 operator+(const Vector3 &vector);

            /// The Vector3 assignment add operator
            ///
            /// @param vector the Vector3 to assignment add
            Vector3 &operator+=(const Vector3 &vector);

            /// The Vector3 remove operator
            ///
            /// @param vector the Vector3 to remove
            Vector3 operator-(const Vector3 &vector);

            /// The Vector3 assignment remove operator
            ///
            /// @param vector the Vector3 to assignment remove
            Vector3 &operator-=(const Vector3 &vector);

            /// The Vector3 multiply operator
            ///
            /// @param vector the Vector3 to multiply
            Vector3 operator*(const Vector3 &vector);

            /// The Vector3 assignment multiply operator
            ///
            /// @param vector the Vector3 to assignment multiply
            Vector3 &operator*=(const Vector3 &vector);

            /// The Vector3 divide operator
            ///
            /// @param vector the Vector3 to divide
            Vector3 operator/(const Vector3 &vector);

            /// The Vector3 assignment divide operator
            ///
            /// @param vector the Vector3 to assignment divide
            Vector3 &operator/=(const Vector3 &vector);

            /// Gets the raylib Vector3
            ///
            /// @return The raylib Vector3
            constexpr const ::Vector3 &asRaylib() const { return {x, y, z}; }

            float x;
            float y;
            float z;
        };
    } // namespace core
} // namespace raylib

#endif /* RAYLIB_CORE_VECTOR3_HPP_ */
