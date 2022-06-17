/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** RenderTexture2D
*/

#include "RenderTexture2D.hpp"

namespace raylib
{
    namespace textures
    {
        RenderTexture2D::RenderTexture2D(unsigned int width, unsigned int height)
            : RenderTexture2D(raylib::core::Vector2u(width, height))
        {
        }

        RenderTexture2D::RenderTexture2D(raylib::core::Vector2u size) { _texture = LoadRenderTexture(size.x, size.y); }

        RenderTexture2D::~RenderTexture2D() { UnloadRenderTexture(_texture); }

        void RenderTexture2D::beginTextureMode(const RenderTexture2D &target) { BeginTextureMode(target._texture); }

        void RenderTexture2D::endTextureMode() { endTextureMode(); }

        const ::RenderTexture2D &RenderTexture2D::asRaylib() const { return _texture; }

        ::RenderTexture2D &RenderTexture2D::asRaylib() { return _texture; }

    } // namespace textures
} // namespace raylib