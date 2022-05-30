/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Image
*/

#ifndef RAYLIB_TEXTURES_IMAGE_HPP_
#define RAYLIB_TEXTURES_IMAGE_HPP_

#include <string>
#include "raylib/core/Vector2.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace textures
    {
        /// This is the Image class. It is a wrapper for the raylib Image class. It has a constructor, a destructor, and
        /// a bunch of functions that wrap the raylib Image functions.
        class Image {
          public:
            /// This function is a constructor for the Image class. It takes in a
            /// Vector2 position, a Color pointer, and a char pointer. It sets the
            /// position to the position passed in, sets the fileName to the fileName
            /// passed in, and then calls the loadImage function
            ///
            /// @param position The position of the image on the screen.
            /// @param color The color of the image.
            /// @param fileName The name of the file to load.
            Image(std::string fileName, Vector2 position = {}, Color *color = {});

            Image(::Image image);

            /// Destructor of Image class
            ~Image() = default;

            /// LoadImage loads an image from a file
            ///
            /// @param fileName The name of the file to load.
            void load();

            /// Loads an image from a texture
            ///
            /// @param texture The texture to load the image from.
            void loadFromTexture(Texture2D &texture);

            /// It loads an image from the screen
            void loadFromScreen(void);

            /// UnloadImage() unloads the image from memory
            void unload();

            /// It exports the image to a file.
            ///
            /// @param fileName The name of the file to export the image to.
            ///
            /// @return A boolean value.
            bool exportTo(const std::string fileName);

            /// It changes the format of the image.
            ///
            /// @param newFormat The new format for the image.
            void format(int newFormat);

            /// It resizes the image to the new width and height.
            ///
            /// @param newWidth The new width of the image.
            /// @param newHeight The new height of the image.
            void resize(int newWidth, int newHeight);

            /// Flips the image vertically
            void flipVertical();

            /// Flips the image horizontally
            void flipHorizontal();

            /// This function rotates the image clockwise by 90 degrees
            void rotateCW();

            /// It rotates the image counter clockwise.
            void rotateCCW();

            /// Tinting the image with the color passed in.
            /// @param color
            void colorTint(Color color);

            /// It inverts the colors of the image.
            void colorInvert();

            /// This function converts an image to grayscale
            void colorGrayscale();

            /// This function changes the contrast of an image.
            ///
            /// @param contrast The contrast to apply to the image.
            void colorContrast(float contrast);

            /// It changes the brightness of the image.
            ///
            /// @param image The image to modify
            /// @param brightness The brightness value.
            void colorBrightness(int brightness);

            /// Replaces all instances of a color in an image with another color.
            ///
            /// @param color The color to replace.
            /// @param replace The color to replace
            void colorReplace(Color &color, Color &replace);

            /// This function loads the color of the image
            ///
            /// @param color The color of the image.
            void loadColors(Color *color);

            /// UnloadImageColors() unloads the image colors from the CPU memory (RAM)
            void unloadColors();

            /// This function returns the color of the image (RGBA)
            ///
            /// @return The color of the image.
            Color *getColor();

          private:
            std::string _fileName;
            Vector2 _position;
            Color *_color;
            ::Image _image;
        };
    } // namespace textures

} // namespace raylib

#endif /* !RAYLIB_TEXTURES_IMAGE_HPP_ */
