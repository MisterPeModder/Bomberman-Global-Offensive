/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Textures
*/

#include "Texture2D.hpp"

namespace raylib
{
    namespace textures
    {

        Texture2D::Texture2D(const std::filesystem::path &fileName, Vector2 position) : _fileName(fileName), _position(position)
        {
            load();
        }

        void Texture2D::setPosition(Vector2 &position) { _position = position; }

        void Texture2D::load() { _texture = LoadTexture(_fileName.c_str()); }

        void Texture2D::loadFromImage(const Image &image) { _texture = LoadTextureFromImage(image); }

        void Texture2D::unload() { UnloadTexture(_texture); }

        void Texture2D::update(std::span<uint32_t> pixels) { UpdateTexture(_texture, pixels.data()); }

        void Texture2D::updateRec(Rectangle &rec, std::span<uint32_t> pixels)
        {
            UpdateTextureRec(_texture, rec, pixels.data());
        }

        void Texture2D::setFilter(int filter) { SetTextureFilter(_texture, filter); }

        void Texture2D::setWrap(int wrap) { SetTextureWrap(_texture, wrap); }

        void Texture2D::draw(const Color &tint) { DrawTexture(_texture, _position.x, _position.y, tint.asRaylib()); }

        void Texture2D::draw(const Vector2 &position, const Color &tint) { DrawTextureV(_texture, position.asRaylib(), tint.asRaylib()); }

        void Texture2D::draw(const Vector2 &position, float rotation, float scale, const Color &tint)
        {
            DrawTextureEx(_texture, position.asRaylib(), rotation, scale, tint.asRaylib());
        }

    } // namespace textures

} // namespace raylib
