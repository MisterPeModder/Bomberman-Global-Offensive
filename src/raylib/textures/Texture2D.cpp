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
        Texture2D::Texture2D(const std::filesystem::path &fileName, Vector2f position)
            : _fileName(fileName), _position(position), _loaded(false)
        {
            load();
        }

        Texture2D::Texture2D() : _fileName(""), _position({}), _loaded(false) {}

        Texture2D::Texture2D(raylib::textures::Image &image) : _loaded(false) { loadFromImage(image.asRaylib()); }

        Texture2D::~Texture2D() { unload(); }

        void Texture2D::setPosition(Vector2f &position) { _position = position; }

        void Texture2D::load(const std::filesystem::path &fileName)
        {
            unload();
            if (!fileName.empty())
                _fileName = fileName;
            _texture = LoadTexture(_fileName.generic_string().c_str());
            _loaded = true;
        }

        void Texture2D::loadFromImage(const ::Image &image)
        {
            unload();
            _texture = LoadTextureFromImage(image);
            _loaded = true;
        }

        void Texture2D::unload()
        {
            if (_loaded) {
                UnloadTexture(_texture);
                _loaded = false;
            }
        }

        void Texture2D::update(std::span<uint32_t> pixels) { UpdateTexture(_texture, pixels.data()); }

        void Texture2D::updateRec(Rectangle &rec, std::span<uint32_t> pixels)
        {
            UpdateTextureRec(_texture, rec, pixels.data());
        }

        void Texture2D::setFilter(int filter) { SetTextureFilter(_texture, filter); }

        void Texture2D::setWrap(int wrap) { SetTextureWrap(_texture, wrap); }

        void Texture2D::draw(const Color &tint) { DrawTexture(_texture, _position.x, _position.y, tint.asRaylib()); }

        void Texture2D::draw(const Vector2f &position, const Color &tint)
        {
            DrawTextureV(_texture, position.asRaylib(), tint.asRaylib());
        }

        void Texture2D::draw(const Vector2f &position, float rotation, float scale, const Color &tint)
        {
            DrawTextureEx(_texture, position.asRaylib(), rotation, scale, tint.asRaylib());
        }

        ::Texture2D &Texture2D::asRaylib() { return _texture; }

        const ::Texture2D &Texture2D::asRaylib() const { return _texture; }

    } // namespace textures

} // namespace raylib
