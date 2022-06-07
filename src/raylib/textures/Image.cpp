/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Image
*/

#include "Image.hpp"

namespace raylib
{
    namespace textures
    {
        Image::Image(
            const std::filesystem::path &fileName, raylib::core::Vector2 position, const raylib::core::Color &color)
            : _fileName(fileName), _position(position), _color(color)
        {
            load();
        }

        Image::~Image() { unload(); }

        void Image::load() { _image = LoadImage(_fileName.generic_string().c_str()); }

        void Image::loadFromTexture(const Texture2D &texture) { _image = LoadImageFromTexture(texture); }

        void Image::loadFromScreen(void) { _image = LoadImageFromScreen(); }

        void Image::unload() { UnloadImage(_image); }

        bool Image::exportTo(const std::filesystem::path &fileName)
        {
            return ExportImage(_image, fileName.generic_string().c_str());
        }

        void Image::format(int newFormat) { ImageFormat(&_image, newFormat); }

        void Image::resize(int newWidth, int newHeight) { ImageResize(&_image, newWidth, newHeight); }

        void Image::flipVertical() { ImageFlipVertical(&_image); }

        void Image::flipHorizontal() { ImageFlipHorizontal(&_image); }

        void Image::rotateCW() { ImageRotateCW(&_image); }

        void Image::rotateCCW() { ImageRotateCCW(&_image); }

        void Image::colorTint(const raylib::core::Color &color) { ImageColorTint(&_image, color.asRaylib()); }

        void Image::colorInvert() { ImageColorInvert(&_image); }

        void Image::colorGrayscale() { ImageColorGrayscale(&_image); }

        void Image::colorContrast(float contrast) { ImageColorContrast(&_image, contrast); }

        void Image::colorBrightness(int brightness) { ImageColorBrightness(&_image, brightness); }

        void Image::colorReplace(const raylib::core::Color &color, const raylib::core::Color &replace)
        {
            ImageColorReplace(&_image, color.asRaylib(), replace.asRaylib());
        }

    } // namespace textures

} // namespace raylib