/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Pixel
*/

#ifndef RAYLIB_SHAPE_PIXEL_HPP_
#define RAYLIB_SHAPE_PIXEL_HPP_

#include "AShape.hpp"
#include "raylib/core/Vector2.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace shapes
    {
        class Pixel : public AShape {
          public:
            /// It creates a pixel with a position and a color.
            ///
            /// @param x The x position of the pixel.
            /// @param y The y position of the pixel.
            /// @param color The color of the pixel.
            Pixel(float x = 0, float y = 0, Color color = {0, 0, 0, 0});

            /// This function is a constructor for the Pixel class. It takes in a
            /// Vector2 and a Color and sets the position and color of the Pixel to the
            /// values passed in
            ///
            /// @param position The position of the pixel.
            /// @param color The color of the pixel.
            Pixel(Vector2 position, Color color);

            /// The destructor for the Pixel class.
            ~Pixel();

            /// Draw a pixel at the position of the pixel object, using the color of the
            /// pixel object.
            void draw() const;
        };
    } // namespace shapes
} // namespace raylib

#endif /* !RAYLIB_SHAPE_PIXEL_HPP_ */
