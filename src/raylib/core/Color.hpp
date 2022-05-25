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

// #pragma region Undefine C Raylib default color macros

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

// #pragma endregion

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

            /// Constructor from an integer
            ///
            /// @param hexColor the hex integer representing the color
            /// @param alpha the alpha (defaulted to 255)
            constexpr Color(int hexColor, unsigned char alpha = 255)
            :
            r(((hexColor >> 16) & 0xFF)),
            g(((hexColor >> 8) & 0xFF)),
            b(((hexColor) & 0xFF)),
            a(alpha)
            {}

            /// Copy assignment operator from an integer
            ///
            /// @param other the hex integer representing the color
            ///
            /// @return The new color
            constexpr Color &operator=(int hexColor)
            {
                r = ((hexColor >> 16) & 0xFF);
                g = ((hexColor >> 8) & 0xFF);
                b = ((hexColor) & 0xFF);
                a = 255;

                return *this;
            }

            /// Gets the raylib Color
            ///
            /// @return The raylib Color
            constexpr ::Color asRaylib() { return {.r = r, .g = g, .b = b, .a = a}; }

            /// Gets the color as integer
            ///
            /// @return The color as integer
            constexpr int asInteger() { return { ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF) }; }

            // #pragma region Default colors

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

            // #pragma endregion

        };

        /// The default colors (same as the ones from the raylib)
        // #pragma region Assingning values to the default colors

        constexpr Color Color::LIGHT_GRAY = Color(200, 200, 200, 255);
        constexpr Color Color::GRAY = Color(130, 130, 130, 255);
        constexpr Color Color::DARK_GRAY = Color(80, 80, 80, 255);
        constexpr Color Color::YELLOW = Color(253, 249, 0, 255);
        constexpr Color Color::GOLD = Color(255, 203, 0, 255);
        constexpr Color Color::ORANGE = Color(255, 161, 0, 255);
        constexpr Color Color::PINK = Color(255, 109, 194, 255);
        constexpr Color Color::RED = Color(230, 41, 55, 255);
        constexpr Color Color::MAROON = Color(190, 33, 55, 255);
        constexpr Color Color::GREEN = Color(0, 228, 48, 255);
        constexpr Color Color::LIME = Color(0, 158, 47, 255);
        constexpr Color Color::DARK_GREEN = Color(0, 117, 44, 255);
        constexpr Color Color::SKY_BLUE = Color(102, 191, 255, 255);
        constexpr Color Color::BLUE = Color(0, 121, 241, 255);
        constexpr Color Color::DARK_BLUE = Color(0, 82, 172, 255);
        constexpr Color Color::PURPLE = Color(200, 122, 255, 255);
        constexpr Color Color::VIOLET = Color(135, 60, 190, 255);
        constexpr Color Color::DARK_PURPLE = Color(112, 31, 126, 255);
        constexpr Color Color::BEIGE = Color(211, 176, 131, 255);
        constexpr Color Color::BROWN = Color(127, 106, 79, 255);
        constexpr Color Color::DARK_BROWN = Color(76, 63, 47, 255);
        constexpr Color Color::WHITE = Color(255, 255, 255, 255);
        constexpr Color Color::BLACK = Color(0, 0, 0, 255);
        constexpr Color Color::BLANK = Color(0, 0, 0, 0);
        constexpr Color Color::MAGENTA = Color(255, 0, 255, 255);
        constexpr Color Color::RAY_WHITE = Color(245, 245, 245, 255);

        // #pragma endregion

    }
}

#endif /* !RAYLIB_CORE_COLOR_HPP_ */
