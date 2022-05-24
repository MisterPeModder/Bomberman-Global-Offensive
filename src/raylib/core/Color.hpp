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
        /// The Color class that encapsulates the raylib Color struct
        class Color {
            public:
                /// Constructor
                ///
                /// @param r the amount of red
                /// @param g the amount of green
                /// @param b the amount of blue
                /// @param a the alpha
                constexpr Color(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255)
                {
                    _color.r = r;
                    _color.g = g;
                    _color.b = b;
                    _color.a = a;
                }

                /// Destructor
                ~Color() = default;

                /// Get the red amount in the color
                ///
                /// @return The red amount
                constexpr unsigned char getRed() const { return _color.r; }

                /// Set the red amount in the color
                ///
                /// @param r The red amount
                constexpr void setRed(unsigned char r) { _color.r = r; }

                /// Get the green amount in the color
                ///
                /// @return The green amount
                constexpr unsigned char getGreen() const { return _color.g; }

                /// Set the green amount in the color
                ///
                /// @param g The green amount
                constexpr void setGreen(unsigned char g) { _color.g = g; }

                /// Get the blue amount in the color
                ///
                /// @return The blue amount
                constexpr unsigned char getBlue() const { return _color.b; }

                /// Set the blue amount in the color
                ///
                /// @param b The blue amount
                constexpr void setBlue(unsigned char b) { _color.b = b; }

                /// Get the alpha of the color
                ///
                /// @return The alpha
                constexpr unsigned char getAlpha() const { return _color.a; }

                /// Set the alpha of the color
                ///
                /// @param a The alpha
                constexpr void setAlpha(unsigned char a) { _color.a = a; }

                /// Gets the raylib Color
                ///
                /// @return The raylib Color
                constexpr ::Color toRaylib() { return _color; }

            private:
                ::Color _color;
};
    }
}

#endif /* !RAYLIB_CORE_COLOR_HPP_ */
