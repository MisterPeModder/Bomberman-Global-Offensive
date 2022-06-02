/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Image
*/

#ifndef RAYLIB_TEXTURES_IMAGE_HPP_
#define RAYLIB_TEXTURES_IMAGE_HPP_

#include <filesystem>
#include "raylib/core/Color.hpp"
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
            Image(const std::filesystem::path &fileName, raylib::core::Vector2 position = {},
                const raylib::core::Color &color = raylib::core::Color::DEFAULT_COLOR);

            Image(::Image image);

            /// Destructor of Image class
            ~Image();

            /// LoadImage loads an image from a file
            ///
            /// @param fileName The name of the file to load.
            void load();

            /// Loads an image from a texture
            ///
            /// @param texture The texture to load the image from.
            void loadFromTexture(const Texture2D &texture);

            /// It loads an image from the screen
            void loadFromScreen(void);

            /// UnloadImage() unloads the image from memory
            void unload();

            /// It exports the image to a file.
            ///
            /// @param fileName The name of the file to export the image to.
            ///
            /// @return A boolean value true if export is good false if ti's not export.
            bool exportTo(const std::filesystem::path &fileName);

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
            void colorTint(const raylib::core::Color &color);

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
            void colorReplace(const raylib::core::Color &color, const raylib::core::Color &replace);

          private:
            std::filesystem::path _fileName;
            raylib::core::Vector2 _position;
            raylib::core::Color _color;
            ::Image _image;
        };
    } // namespace textures

} // namespace raylib

#endif /* !RAYLIB_TEXTURES_IMAGE_HPP_ */
