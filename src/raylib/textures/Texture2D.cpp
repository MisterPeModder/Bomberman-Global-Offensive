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

        Texture2D::Texture2D(char *fileName, Vector2 position) : _fileName(fileName), _position(position)
        {
            loadTexture();
        }

        void Texture2D::setPosition(Vector2 &position) { _position = position; }

        void Texture2D::loadTexture() { _texture = LoadTexture(_fileName); }

        void Texture2D::loadTextureFromImage(Image &image) { _texture = LoadTextureFromImage(image); }

        void Texture2D::unloadTexture() { UnloadTexture(_texture); }

        void Texture2D::updateTexture(std::span<uint32_t> *pixels) { UpdateTexture(_texture, pixels); }

        void Texture2D::updateTextureRec(Rectangle &rec, std::span<uint32_t> *pixels)
        {
            UpdateTextureRec(_texture, rec, pixels);
        }

        void Texture2D::setTextureFilter(int filter) { SetTextureFilter(_texture, filter); }

        void Texture2D::setTextureWrap(int wrap) { SetTextureWrap(_texture, wrap); }

        void Texture2D::drawTexture(Color &tint) { DrawTexture(_texture, _position.x, _position.y, tint); }

        void Texture2D::drawTexture(Vector2 &position, Color &tint) { DrawTextureV(_texture, position, tint); }

        void Texture2D::drawTexture(Vector2 &position, float rotation, float scale, Color &tint)
        {
            DrawTextureEx(_texture, position, rotation, scale, tint);
        }

    } // namespace textures

} // namespace raylib
