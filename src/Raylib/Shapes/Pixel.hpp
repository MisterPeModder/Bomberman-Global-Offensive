/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Pixel
*/

#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include "../Core/Vector2.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace shapes
    {
        class Pixel {
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
            void draw();

            /// This function sets the color of the pixel to the given color.
            ///
            /// @param color The color to set the pixel to.
            /// @param format The format of the pixel. This is a float value between 0
            /// and 1.
            void setColor(Color color, float format);

            /// This function returns the color of the pixel.
            ///
            /// @param format The format of the image. This is a float value between 0
            /// and 1.
            ///
            /// @return The color of the pixel.
            Color getColor(float format);

            /// This function sets the position of the pixel to the position passed in
            ///
            /// @param position The position of the pixel.
            void setPosition(Vector2 position);

            /// This function returns the position of the pixel
            ///
            /// @return The position of the pixel.
            Vector2 getPosition();

          protected:
          private:
            Vector2 _position;
            Color _color;
        };
    } // namespace shapes
} // namespace raylib

#endif /* !PIXEL_HPP_ */
