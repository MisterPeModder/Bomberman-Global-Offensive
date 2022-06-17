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
        class RenderTexture2D {
          public:
            RenderTexture2D(unsigned int width = raylib::core::Window::getWidth(),
                unsigned int height = raylib::core::Window::getHeight());

            RenderTexture2D(raylib::core::Vector2u size);

            ~RenderTexture2D();

            static void beginTextureMode(const RenderTexture2D &target);
            static void endTextureMode();

            const ::RenderTexture2D &asRaylib() const;
            ::RenderTexture2D &asRaylib();

          private:
            ::RenderTexture2D _texture;
        };
    } // namespace textures
} // namespace raylib

#endif /* !RAYLIB_TEXTURES_RENDERTEXTURE2D_HPP_ */
