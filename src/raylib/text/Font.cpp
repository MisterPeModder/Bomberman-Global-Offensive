/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Raylib text module: Font
*/

#include "Font.hpp"

extern "C"
{
#include <raylib.h>
}

#include <filesystem>
#include <span>
#include <utility>
#include <string_view>

namespace raylib::text
{
    Font::Font() noexcept : _initialized(false) {}

    Font::Font(::Font &&raylibFont) noexcept : _initialized(true), _font(std::move(raylibFont)) {}

    Font::Font(std::filesystem::path const &path) : _initialized(true), _font(::LoadFont(path.generic_string().c_str()))
    {
    }

    Font::Font(std::filesystem::path const &path, int size, int *chars, int glyphCount)
        : _initialized(true), _font(::LoadFontEx(path.generic_string().c_str(), size, chars, glyphCount))
    {
    }

    Font::Font(std::string_view fileType, std::span<unsigned char const> data, int size, int *chars, int glyphCount)
        : _initialized(true),
          _font(::LoadFontFromMemory(fileType.data(), data.data(), data.size_bytes(), size, chars, glyphCount))
    {
    }

    Font::Font(Font &&other) : _initialized(other._initialized), _font(std::move(other._font))
    {
        other._initialized = false;
    }

    Font::~Font()
    {
        if (this->_initialized) {
            UnloadFont(this->_font);
            this->_initialized = false;
        }
    }

    Font Font::getDefault() noexcept { return Font(::GetFontDefault()); }

    raylib::core::Vector2f Font::measure(std::string_view str, float size, float spacing) const noexcept
    {
        return raylib::core::Vector2f(::MeasureTextEx(this->_font, str.data(), size, spacing));
    }

    void Font::draw(
        std::string_view str, raylib::core::Vector2f pos, float fontSize, raylib::core::Color tint, float spacing) const
    {
        ::DrawTextEx(this->_font, str.data(), pos.asRaylib(), fontSize, spacing, tint.asRaylib());
    }

    void Font::draw(std::string_view str, raylib::core::Vector2f pos, raylib::core::Vector2f origin, float rotation,
        float fontSize, raylib::core::Color tint, float spacing) const
    {
        ::DrawTextPro(
            this->_font, str.data(), pos.asRaylib(), origin.asRaylib(), rotation, fontSize, spacing, tint.asRaylib());
    }

    void Font::draw(int codepoint, raylib::core::Vector2f pos, float fontSize, raylib::core::Color tint) const
    {
        ::DrawTextCodepoint(this->_font, codepoint, pos.asRaylib(), fontSize, tint.asRaylib());
    }

} // namespace raylib::text
