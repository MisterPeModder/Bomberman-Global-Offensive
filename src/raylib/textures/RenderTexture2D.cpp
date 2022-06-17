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
        RenderTexture2D::RenderTexture2D(int width, int height) : RenderTexture2D(raylib::core::Vector2i(width, height))
        {
        }

        RenderTexture2D::RenderTexture2D(raylib::core::Vector2i size) { _texture = LoadRenderTexture(size.x, size.y); }

        RenderTexture2D::~RenderTexture2D() { UnloadRenderTexture(_texture); }

        void RenderTexture2D::beginTextureMode(const RenderTexture2D &target) { BeginTextureMode(target._texture); }

        void RenderTexture2D::endTextureMode() { EndTextureMode(); }

        void RenderTexture2D::drawYFlipped() const
        {
            DrawTextureRec(_texture.texture,
                {0, 0, static_cast<float>(_texture.texture.width), static_cast<float>(-_texture.texture.height)},
                {0, 0}, raylib::core::Color::WHITE.asRaylib());
        }

        const ::RenderTexture2D &RenderTexture2D::asRaylib() const { return _texture; }

        ::RenderTexture2D &RenderTexture2D::asRaylib() { return _texture; }

    } // namespace textures
} // namespace raylib