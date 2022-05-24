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
            loadImage();
        }

        void Image::loadImage() { _image = LoadImage(_fileName.c_str()); }

        void Image::loadImageFromTexture(Texture2D &texture) { _image = LoadImageFromTexture(texture); }

        void Image::loadImageFromScreen(void) { _image = LoadImageFromScreen(); }

        void Image::unloadImage() { UnloadImage(_image); }

        bool Image::exportImage(const std::string fileName) { return ExportImage(_image, fileName.c_str()); }

        void Image::imageFormat(int newFormat) { ImageFormat(&_image, newFormat); }

        void Image::imageResize(int newWidth, int newHeight) { ImageResize(&_image, newWidth, newHeight); }

        void Image::imageFlipVertical() { ImageFlipVertical(&_image); }

        void Image::imageFlipHorizontal() { ImageFlipHorizontal(&_image); }

        void Image::imageRotateCW() { ImageRotateCW(&_image); }

        void Image::imageRotateCCW() { ImageRotateCCW(&_image); }

        void Image::imageColorTint(Color color) { ImageColorTint(&_image, color); }

        void Image::imageColorInvert() { ImageColorInvert(&_image); }

        void Image::imageColorGrayscale() { ImageColorGrayscale(&_image); }

        void Image::imageColorContrast(float contrast) { ImageColorContrast(&_image, contrast); }

        void Image::imageColorBrightness(int brightness) { ImageColorBrightness(&_image, brightness); }

        void Image::imageColorReplace(Color &color, Color &replace) { ImageColorReplace(&_image, color, replace); }

        void Image::loadImageColors(Color *color) { _color = color; }

        void Image::unloadImageColors() { UnloadImageColors(_color); }

        Color Image::getImageColor(Image &image, int x, int y) { return getImageColor(image, x, y); }

        Color *Image::getColor() { return _color; }

    } // namespace textures

} // namespace raylib
