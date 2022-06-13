/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Textures
*/

#ifndef RAYLIB_TEXTURES_TEXTURE2D_HPP_
#define RAYLIB_TEXTURES_TEXTURE2D_HPP_

#include <filesystem>
#include <iostream>
#include <span>
#include "raylib/core/Color.hpp"
#include "raylib/core/Vector2.hpp"
#include "raylib/textures/Image.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace textures
    {
        /// This is the class that is used to create a texture2D object.
        class Texture2D {
          private:
            using Vector2f = raylib::core::Vector2f;
            using Color = raylib::core::Color;

          public:
            /// This function takes in a position and a file name and sets the position
            /// and file name of the texture to the values passed in
            ///
            /// @param position The position of the texture on the screen.
            /// @param fileName The name of the file that contains the texture.
            Texture2D(const std::filesystem::path &fileName, Vector2f position = {});

            /// The destructor for the Texture2D class
            ~Texture2D();

            /// Sets the position of the texture
            ///
            /// @param position The position of the texture.
            void setPosition(Vector2f &position);

            /// The function `loadTexture()` loads a texture from a file
            void load();

            /// Loads a texture from an Image object
            ///
            /// @param image The image to load the texture from.
            void loadFromImage(const ::Image &image);

            /// UnloadTexture() is a function that unloads a texture from GPU memory
            void unload();

            /// It updates the texture with the given pixels.
            ///
            /// @param pixels The pixel data to update the texture with.
            void update(std::span<uint32_t> pixels);

            /// It updates the texture with new pixel data.
            ///
            /// @param rec The rectangle to update.
            /// @param pixels The pixel data to be uploaded to the GPU.
            void updateRec(Rectangle &rec, std::span<uint32_t> pixels);

            /// It sets the texture filter.
            ///
            /// @param filter
            void setFilter(int filter);

            /// Sets the texture wrap mode,
            /// Set texture scaling filter mode
            /// Case of use https://www.raylib.com/examples/text/loader.html?name=text_font_filters
            ///
            /// @param wrap GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE,
            /// GL_CLAMP_TO_BORDER
            void setWrap(int wrap);

            /// Draws the texture2D at the position specified by the position variable
            ///
            /// @param tint The color you want to tint the texture2D.
            void draw(const Color &tint);

            /// Draws a texture2D at a given position with a given tint
            ///
            /// @param position The position of the texture2D on the screen.
            /// @param tint The color you want to tint the texture2D.
            void draw(const Vector2f &position, const Color &tint);

            /// Draws a Texture2D with extended parameters
            ///
            /// @param position The position of the texture2D.
            /// @param rotation The rotation of the texture2D in radians.
            /// @param scale The scale of the texture2D.
            /// @param tint The color to tint the texture2D with.
            void draw(const Vector2f &position, float rotation, float scale, const Color &tint);

            /// Gets the C Raylib mutable version of the 2d texture
            ///
            /// @return The raylib version of the 2d texture
            ::Texture2D &asRaylib();

            /// Gets the C Raylib const version of the 2d texture
            ///
            /// @return The raylib version of the 2d texture
            const ::Texture2D &asRaylib() const;

          private:
            std::filesystem::path _fileName;
            Vector2f _position;
            ::Texture2D _texture;
        };

    } // namespace textures

} // namespace raylib

#endif /* !RAYLIB_TEXTURES_TEXTURE2D_HPP_ */
