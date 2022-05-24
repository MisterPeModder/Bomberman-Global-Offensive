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

        Texture2D::Texture2D(Vector2 position, char *fileName)
        {
            _fileName = fileName;
            _position = position;
            _texture = loadTexture();
        }

        Texture2D::~Texture2D()
        {

        }

        Texture2D::setPosition(Vector2 position)
        {
            _position = position;
        }

        Texture2D Texture2D::loadTexture()
        {
            LoadTexture(_fileName);
        }

        void Texture2D::loadTextureFromImage(Image image)
        {
            _texture = LoadTextureFromImage(image);
        }

        void Texture2D::unloadTexture()
        {
            UnloadTexture(_texture);
        }

        
        void Texture2D::updateTexture(const void *pixels)
        {
            UpdateTexture(_texture, pixels);
        }

       
        void Texture2D::updateTextureRec(Rectangle rec, const void *pixels)
        {
            UpdatetextureRec(_texture, rec, pixels);
        }

       
        void Texture2D::setTextureFilter(int filter)
        {
            SetTextureFilter(_texture, filter)
        }

        
        void Texture2D::setTextureWrap(int wrap)
        {
            SetTextureWrap(_texture, wrap);
        }

        
        void Texture2D::drawTexture(Color tint)
        {
            Drawtexture(_texture, _position.x, _position.y, tint);
        }

        
        void Texture2D::drawTextureV(Vector2 position, Color tint)
        {
            DrawtextureV(_texture, position, tint);
        }

        void Texture2D::drawTextureEx(Vector2 position, float rotation, float scale, Color tint)
        {
            DrawTextureEx(_texture, position, rotation, scale, tint);
        }

    } // namespace textures

} // namespace raylib
