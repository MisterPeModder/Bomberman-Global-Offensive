/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Image
*/

#include "Image.hpp"
#include "raylib/core/Vector2.h"
namespace raylib
{
    namespace textures
    {

        Images::Image(Vector2 position, Color *color, char *fileName) : _position(position), _fileName(fileName)
        {
            loadImage(_fileName);
        }

        void Images::loadImage(const char *fileName) { _image = LoadImage(fileName); }

        void Images::loadImageFromTexture(Texture2D &texture) { _image = LoadImageFromTexture(texture); }

        void Images::loadImageFromScreen(void) { _image = LoadImageFromScreen(); }

        void Images::unloadImage() { UnloadImage(_image); }

        bool Images::exportImage(const char *fileName) { return ExportImage(_image, filename); }

        Images::Image Images::imageFromImage(Rectangle &rec) { return ImageFromImage(_image, rec); }

        void Images::imageFormat(int newFormat) { Imageformat(_image, newFormat); }

        void Images::imageResize(int newWidth, int newHeight) { ImageResize(_image, newWidth, newHeight); }

        void Images::imageFlipVertical() { ImageFlipVertical(_image); }

        void Images::imageFlipHorizontal() { ImageFlipHorizontal(_image); }

        void Images::imageRotateCW() { ImageRotateCW(_image); }

        void Images::imageRotateCCW() { ImageRotateCCW(_image); }

        void Images::imageColorTint(Color color) { ImageColorTint(_image, color) }

        void Images::imageColorInvert() { ImageColorInvert(_image); }

        void Images::imageColorGrayscale() { ImageColorGrayscale(_image); }

        void Images::imageColorContrast(float contrast) { ImageColorContrast(_image, contrast); }

        void Images::imageColorBrightness(Image *image, int brightness) { ImageColorBrightness(_image, brightness); }

        void Images::imageColorReplace(Color &color, Color &replace) { ImageColorReplace(_image, color, replace); }

        void Images::loadImageColors(Color *color) { _color = color; }

        void Images::unloadImageColors() { UnloadImageColors(_color); }

        Color Images::getImageColor(Image &image, int x, int y) { return getImageColor(_image, x, y); }

        Color Images::getColor() { return _color; }

    } // namespace textures

} // namespace raylib
