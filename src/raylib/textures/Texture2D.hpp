/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Textures
*/

#ifndef TEXTURES_HPP_
#define TEXTURES_HPP_

#include "raylib/core/Vector2.hpp"
#include <span>
#include <iostream>
extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace textures
    {
        class Texture2D {
          public:
            /// This function takes in a position and a file name and sets the position
            /// and file name of the texture to the values passed in
            ///
            /// @param position The position of the texture on the screen.
            /// @param fileName The name of the file that contains the texture.
            Texture2D(char *fileName, Vector2 position = {});

            /// The destructor for the Texture2D class
            ~Texture2D() = default;

            /// Sets the position of the texture
            ///
            /// @param position The position of the texture.
            void setPosition(Vector2 &position);

            /// The function `loadTexture()` loads a texture from a file
            void loadTexture();

            /// Loads a texture from an Image object
            ///
            /// @param image The image to load the texture from.
            void loadTextureFromImage(Image &image);

            /// UnloadTexture() is a function that unloads a texture from GPU memory
            void unloadTexture();

            /// It updates the texture with the given pixels.
            ///
            /// @param pixels The pixel data to update the texture with.
            void updateTexture(std::span<uint32_t> *pixels);

            /// It updates the texture with new pixel data.
            ///
            /// @param rec The rectangle to update.
            /// @param pixels The pixel data to be uploaded to the GPU.
            void updateTextureRec(Rectangle &rec, std::span<uint32_t> *pixels);

            /// It sets the texture filter.
            ///
            /// @param filter
            void setTextureFilter(int filter);

            /// Sets the texture wrap mode,
            /// Set texture scaling filter mode
            /// Case of use https://www.raylib.com/examples/text/loader.html?name=text_font_filters
            ///
            /// @param wrap GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE,
            /// GL_CLAMP_TO_BORDER
            void setTextureWrap(int wrap);

            /// Draws the texture2D at the position specified by the position variable
            ///
            /// @param tint The color you want to tint the texture2D.
            void drawTexture(Color &tint);

            /// Draws a texture2D at a given position with a given tint
            ///
            /// @param position The position of the texture2D on the screen.
            /// @param tint The color you want to tint the texture2D.
            void drawTexture(Vector2 &position, Color &tint);

            /// Draws a Texture2D with extended parameters
            ///
            /// @param position The position of the texture2D.
            /// @param rotation The rotation of the texture2D in radians.
            /// @param scale The scale of the texture2D.
            /// @param tint The color to tint the texture2D with.
            void drawTexture(Vector2 &position, float rotation, float scale, Color &tint);

          private:
            char *_fileName;
            Vector2 _position;
            ::Texture2D _texture;
        };

    } // namespace textures

} // namespace raylib

#endif /* !TEXTURES_HPP_ */
