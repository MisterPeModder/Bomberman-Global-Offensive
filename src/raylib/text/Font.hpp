/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Raylib text module: Font
*/

#ifndef RAYLIB_TEXT_FONT_HPP_
#define RAYLIB_TEXT_FONT_HPP_

#include "raylib/core/Vector2.hpp"

extern "C"
{
#include <raylib.h>
}

#include <filesystem>
#include <span>
#include <string_view>

/// Raylib text module.
namespace raylib::text
{
    class Font {
      public:
        /// Default (uninitialized) constructor.
        Font() noexcept;

        /// Construct a Font from a raylib font structure.
        ///
        /// @param raylibFont Raw raylib font.
        Font(::Font &&raylibFont) noexcept;

        /// Loads a font from the given path.
        ///
        /// @param path The font file path.
        Font(std::filesystem::path const &path);

        /// Loads a font from the given path.
        ///
        /// @param path The font file path.
        /// @param size The font's size.
        /// @param chars The Unicode codepoints supported by the font, may be @b nullptr.
        /// @param glyphCount The number of glyphs in the font.
        Font(std::filesystem::path const &path, int size, int *chars, int glyphCount);

        /// Loads a font from memory.
        ///
        /// @param fileType The file type, only ".ttf" and ".otf" are supported.
        /// @param data The font's raw data.
        /// @param size The font's size.
        /// @param chars The Unicode codepoints supported by the font, may be @b nullptr.
        /// @param glyphCount The number of glyphs in the font.
        Font(std::string_view fileType, std::span<unsigned char const> data, int size, int *chars, int glyphCount);

        /// Cannot copy fonts.
        Font(Font const &) = delete;

        /// Move constructor.
        Font(Font &&);

        /// Destructor.
        ~Font();

        /// @returns The default font instance.
        static Font getDefault() noexcept;

        /// @returns A constant reference to the inner raylib font object.
        constexpr ::Font const &asRaylib() const noexcept { return this->_font; }

        /// @returns A mutable reference to the inner raylib font object.
        constexpr ::Font &asRaylib() noexcept { return this->_font; }

        /// Measure the size that @b str will occupy once rendered.
        ///
        /// @param str The string to measure, must be nul-terminated.
        /// @param size The font size.
        /// @param spacing Space between characters.
        ///
        /// @returns The rendered font size.
        raylib::core::Vector2f measure(std::string_view str, float size, float spacing = 1.0f);

      private:
        bool _initialized;
        ::Font _font;
    };
} // namespace raylib::text

#endif // !defined(RAYLIB_TEXT_FONT_HPP_)
