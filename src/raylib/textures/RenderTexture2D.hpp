/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** RenderTexture2D
*/

#ifndef RAYLIB_TEXTURES_RENDERTEXTURE2D_HPP_
#define RAYLIB_TEXTURES_RENDERTEXTURE2D_HPP_

#include "raylib/core/Vector2.hpp"
#include "raylib/core/Window.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace textures
    {
        /// Render Texture 2D
        class RenderTexture2D {
          public:
            /// Construct a new Render Texture object.
            ///
            /// @param width width of the texture.
            /// @param height height of the texture.
            RenderTexture2D(int width, int height);

            /// Construct a new Render Texture object.
            ///
            /// @param size size of the texture.
            RenderTexture2D(raylib::core::Vector2i size);

            /// Destroy the Render Texture.
            ~RenderTexture2D();

            /// Starts a global texture draw context.
            ///
            /// @param target texture onto draw must occurs.
            static void beginTextureMode(const RenderTexture2D &target);

            /// Stops a global texture draw context.
            static void endTextureMode();

            /// Draw the texture with a y flip.
            /// @note This function is usefull because of OpenGL coordinates (left-bottom).
            void drawYFlipped() const;

            /// Get the raylib RenderTexture2D object.
            ///
            /// @return const ::RenderTexture2D& render texture.
            const ::RenderTexture2D &asRaylib() const;

            /// Get the raylib RenderTexture2D object.
            ///
            /// @return ::RenderTexture2D& render texture.
            ::RenderTexture2D &asRaylib();

          private:
            ::RenderTexture2D _texture;
        };
    } // namespace textures
} // namespace raylib

#endif /* !RAYLIB_TEXTURES_RENDERTEXTURE2D_HPP_ */
