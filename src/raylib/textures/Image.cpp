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
            const std::filesystem::path &fileName, raylib::core::Vector2f position, const raylib::core::Color &color)
            : _fileName(fileName), _position(position), _color(color)
        {
            load();
        }

        Image::~Image() { unload(); }

        void Image::load()
        {
            _image = LoadImage(_fileName.generic_string().c_str());
            _loaded = true;
        }

        void Image::loadFromTexture(const Texture2D &texture)
        {
            _image = LoadImageFromTexture(texture);
            _loaded = true;
        }

        void Image::loadFromScreen(void)
        {
            _image = LoadImageFromScreen();
            _loaded = true;
        }

        void Image::unload()
        {
            if (_loaded) {
                UnloadImage(_image);
                _loaded = false;
            }
        }

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

        const ::Image &Image::asRaylib() const { return _image; }

        ::Image &Image::asRaylib() { return _image; }

    } // namespace textures

} // namespace raylib
