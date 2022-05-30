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

        Texture2D::Texture2D(std::string fileName, Vector2 position) : _fileName(fileName), _position(position)
        {
            load();
        }

        void Texture2D::setPosition(Vector2 &position) { _position = position; }

        void Texture2D::load() { _texture = LoadTexture(_fileName.c_str()); }

        void Texture2D::loadFromImage(Image &image) { _texture = LoadTextureFromImage(image); }

        void Texture2D::unload() { UnloadTexture(_texture); }

        void Texture2D::update(std::span<uint32_t> pixels) { UpdateTexture(_texture, pixels.data()); }

        void Texture2D::updateRec(Rectangle &rec, std::span<uint32_t> pixels)
        {
            UpdateTextureRec(_texture, rec, pixels.data());
        }

        void Texture2D::setFilter(int filter) { SetTextureFilter(_texture, filter); }

        void Texture2D::setWrap(int wrap) { SetTextureWrap(_texture, wrap); }

        void Texture2D::draw(Color &tint) { DrawTexture(_texture, _position.x, _position.y, tint); }

        void Texture2D::draw(Vector2 &position, Color &tint) { DrawTextureV(_texture, position, tint); }

        void Texture2D::draw(Vector2 &position, float rotation, float scale, Color &tint)
        {
            DrawTextureEx(_texture, position, rotation, scale, tint);
        }

    } // namespace textures

} // namespace raylib
