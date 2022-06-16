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

    raylib::core::Vector2f Font::measure(std::string_view str, float size, float spacing)
    {
        return raylib::core::Vector2f(::MeasureTextEx(this->_font, str.data(), size, spacing));
    }

} // namespace raylib::text
