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
        Image::Image(std::string fileName, Vector2 position, Color *color) :_fileName(fileName), _position(position), _color(color)
        {
            load();
        }

        void Image::load() { _image = LoadImage(_fileName.c_str()); }

        void Image::loadFromTexture(Texture2D &texture) { _image = LoadImageFromTexture(texture); }

        void Image::loadFromScreen(void) { _image = LoadImageFromScreen(); }

        void Image::unload() { UnloadImage(_image); }

        bool Image::exportTo(const std::string fileName) { return ExportImage(_image, fileName.c_str()); }

        void Image::format(int newFormat) { ImageFormat(&_image, newFormat); }

        void Image::resize(int newWidth, int newHeight) { ImageResize(&_image, newWidth, newHeight); }

        void Image::flipVertical() { ImageFlipVertical(&_image); }

        void Image::flipHorizontal() { ImageFlipHorizontal(&_image); }

        void Image::rotateCW() { ImageRotateCW(&_image); }

        void Image::rotateCCW() { ImageRotateCCW(&_image); }

        void Image::colorTint(Color color) { ImageColorTint(&_image, color); }

        void Image::colorInvert() { ImageColorInvert(&_image); }

        void Image::colorGrayscale() { ImageColorGrayscale(&_image); }

        void Image::colorContrast(float contrast) { ImageColorContrast(&_image, contrast); }

        void Image::colorBrightness(int brightness) { ImageColorBrightness(&_image, brightness); }

        void Image::colorReplace(Color &color, Color &replace) { ImageColorReplace(&_image, color, replace); }

        void Image::loadColors(Color *color) { _color = color; }

        void Image::unloadColors() { UnloadImageColors(_color); }

        Color *Image::getColor() { return _color; }

    } // namespace textures

} // namespace raylib
