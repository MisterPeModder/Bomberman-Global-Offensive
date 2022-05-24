/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Color
*/

#ifndef RAYLIB_CORE_COLOR_HPP_
#define RAYLIB_CORE_COLOR_HPP_

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace core
    {
        /// The Color struct that encapsulates the raylib Color struct
        struct Color {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;

            /// Constructor with the red, green and blue values mandatory
            ///
            /// @param red the amount of red
            /// @param green the amount of green
            /// @param blue the amount of blue
            /// @param alpha the alpha (defaulted to 255)
            constexpr Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255) : r(red), g(green), b(blue), a(alpha) {}

            /// Default constructor
            /// Defaults everything to 255
            constexpr Color() : r(255), g(255), b(255), a(255) {}

            /// Destructor
            ~Color() = default;

            /// Copy constructor
            ///
            /// @param other The color to copy
            constexpr Color(const Color &other) : r(other.r), g(other.g), b(other.b), a(other.a) {}

            /// Copy assignment operator
            ///
            /// @param other The color to copy
            ///
            /// @return The new copied color
            constexpr Color &operator=(const Color &other)
            {
                r = other.r;
                g = other.g;
                b = other.b;
                a = other.a;

                return *this;
            }

            /// Constructor from the C Raylib Color struct
            ///
            /// @param other The C Raylib color to copy
            constexpr Color(const ::Color &other) : r(other.r), g(other.g), b(other.b), a(other.a) {}

            /// Copy assignment operator from a C Raylib Color struct
            ///
            /// @param other The C Raylib color to copy
            ///
            /// @return The new copied color
            constexpr Color &operator=(const ::Color &other)
            {
                r = other.r;
                g = other.g;
                b = other.b;
                a = other.a;

                return *this;
            }

            /// Gets the raylib Color
            ///
            /// @return The raylib Color
            constexpr ::Color asRaylib() { return {.r = r, .g = g, .b = b, .a = a}; }

        };
    }
}

#endif /* !RAYLIB_CORE_COLOR_HPP_ */
