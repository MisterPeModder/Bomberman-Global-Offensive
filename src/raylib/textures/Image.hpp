/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Image
*/

#ifndef RAYLIB_TEXTURES_IMAGE_HPP_
#define RAYLIB_TEXTURES_IMAGE_HPP_

#include <string>
#include <filesystem>
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
            /// position to the position passed in, sets the filePath to the filePath
            /// passed in, and then calls the loadImage function
            ///
            /// @param position The position of the image on the screen.
            /// @param color The color of the image.
            /// @param filePath The name of the file to load.
            Image(std::filesystem::path &filePath , Vector2 position = {}, Color *color = {});

            /// This function is a constructor for the Image class. It takes in a
            /// Image of raylib. It sets the
            /// position to the position passed in, sets the filePath to the filePath
            /// passed in, and then calls the loadImage function
            ///
            /// @param image class of the raylib
            Image(::Image image);

            /// Destructor of Image class
            ~Image() = default;

            /// LoadImage loads an image from a file
            ///
            /// @param filePath The name of the file to load.
            void loadImage();

            /// Loads an image from a texture
            ///
            /// @param texture The texture to load the image from.
            void loadImageFromTexture(Texture2D &texture);

            /// It loads an image from the screen
            void loadImageFromScreen(void);

            /// UnloadImage() unloads the image from memory
            void unloadImage();

            /// It exports the image to a file.
            ///
            /// @param filePath The name of the file to export the image to.
            ///
            /// @return A boolean value.
            bool exportImage(const std::filesystem::path &filePath );

            /// It changes the format of the image.
            ///
            /// @param newFormat The new format for the image.
            void imageFormat(int newFormat);

            /// It resizes the image to the new width and height.
            ///
            /// @param newWidth The new width of the image.
            /// @param newHeight The new height of the image.
            void imageResize(int newWidth, int newHeight);

            /// Flips the image vertically
            void imageFlipVertical();

            /// Flips the image horizontally
            void imageFlipHorizontal();

            /// This function rotates the image clockwise by 90 degrees
            void imageRotateCW();

            /// It rotates the image counter clockwise.
            void imageRotateCCW();

            /// Tinting the image with the color passed in.
            /// @param color
            void imageColorTint(Color color);

            /// It inverts the colors of the image.
            void imageColorInvert();

            /// This function converts an image to grayscale
            void imageColorGrayscale();

            /// This function changes the contrast of an image.
            ///
            /// @param contrast The contrast to apply to the image.
            void imageColorContrast(float contrast);

            /// It changes the brightness of the image.
            ///
            /// @param image The image to modify
            /// @param brightness The brightness value.
            void imageColorBrightness(int brightness);

            /// Replaces all instances of a color in an image with another color.
            ///
            /// @param color The color to replace.
            /// @param replace The color to replace
            void imageColorReplace(Color &color, Color &replace);

            /// This function loads the color of the image
            ///
            /// @param color The color of the image.
            void loadImageColors(Color *color);

            /// UnloadImageColors() unloads the image colors from the CPU memory (RAM)
            void unloadImageColors();

            /// It returns the color of the pixel at the given coordinates.
            ///
            /// @param image The image to get the color from.
            /// @param x The x coordinate of the pixel to get the color of.
            /// @param y The y coordinate of the pixel to get the color of.
            ///
            /// @return A Color object.
            Color getImageColor(Image &image, int x, int y);

            /// This function returns the color of the image (RGBA)
            ///
            /// @return The color of the image.
            Color *getColor();

          private:
            std::filesystem::path _filePath;
            Vector2 _position;
            Color *_color;
            ::Image _image;
        };
    } // namespace textures

} // namespace raylib

#endif /* !RAYLIB_TEXTURES_IMAGE_HPP_ */
