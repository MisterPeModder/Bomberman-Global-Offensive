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

#pragma region Undefine C Raylib default color macros

#undef LIGHTGRAY
#undef GRAY
#undef DARKGRAY
#undef YELLOW
#undef GOLD
#undef ORANGE
#undef PINK
#undef RED
#undef MAROON
#undef GREEN
#undef LIME
#undef DARKGREEN
#undef SKYBLUE
#undef BLUE
#undef DARKBLUE
#undef PURPLE
#undef VIOLET
#undef DARKPURPLE
#undef BEIGE
#undef BROWN
#undef DARKBROWN
#undef WHITE
#undef BLACK
#undef BLANK
#undef MAGENTA
#undef RAYWHITE

#pragma endregion

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
            constexpr Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
                : r(red), g(green), b(blue), a(alpha)
            {
            }

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

            /// Constructor from an integer
            ///
            /// @param hexColor the hex integer representing the color
            /// @param alpha the alpha (defaulted to 255)
            constexpr Color(int hexColor, unsigned char alpha = 255)
                : r(((hexColor >> 16) & 0xFF)), g(((hexColor >> 8) & 0xFF)), b(((hexColor)&0xFF)), a(alpha)
            {
            }

            /// Copy assignment operator from an integer
            ///
            /// @param other the hex integer representing the color
            ///
            /// @return The new color
            constexpr Color &operator=(int hexColor)
            {
                r = ((hexColor >> 16) & 0xFF);
                g = ((hexColor >> 8) & 0xFF);
                b = ((hexColor)&0xFF);
                a = 255;

                return *this;
            }

            /// Gets the raylib Color
            ///
            /// @return The raylib Color
            constexpr ::Color asRaylib() const { return {.r = r, .g = g, .b = b, .a = a}; }

            /// Gets the color as integer
            ///
            /// @return The color as integer
            constexpr int asInteger() { return ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF); }

#pragma region Default colors

            static const Color LIGHT_GRAY;
            static const Color GRAY;
            static const Color DARK_GRAY;
            static const Color YELLOW;
            static const Color GOLD;
            static const Color ORANGE;
            static const Color PINK;
            static const Color RED;
            static const Color MAROON;
            static const Color GREEN;
            static const Color LIME;
            static const Color DARK_GREEN;
            static const Color SKY_BLUE;
            static const Color BLUE;
            static const Color DARK_BLUE;
            static const Color PURPLE;
            static const Color VIOLET;
            static const Color DARK_PURPLE;
            static const Color BEIGE;
            static const Color BROWN;
            static const Color DARK_BROWN;
            static const Color WHITE;
            static const Color BLACK;
            static const Color BLANK;
            static const Color MAGENTA;
            static const Color RAY_WHITE;

#pragma endregion
        };
    } // namespace core
} // namespace raylib

#endif /* !RAYLIB_CORE_COLOR_HPP_ */
