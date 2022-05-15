/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Pixel
*/

#ifndef PIXEL_HPP_
#define PIXEL_HPP_

#include "../Core/Vector2.hpp"

extern "C" {
    #include "raylib.h"
}

namespace raylib {
    namespace Shapes {
        class Pixel {
            public:
                
                /// @brief This is the constructor for the Pixel class. It takes in a Color object and two
                /// integers, and sets the position and color of the Pixel object
                /// 
                /// @param color The color of the pixel.
                /// @param x The x position of the pixel
                /// @param y The y position of the pixel
                Pixel(Color color, int x = 0, int y = 0);
                
                /// @brief A constructor for the Pixel class.
                /// 
                /// @param position The position of the pixel.
                /// @param color The color of the pixel.
                Pixel(Vector2 position, Color color);
                
                /// @brief Destructor
                ~Pixel();

                /// Draws a pixel
                /// 
                /// @param posX The x position of the pixel
                /// @param posY The Y position of the pixel
                /// @param color The color of the pixel.
                void drawPixel(int posX, int posY, Color color);
                
                /// @brief Draws a pixel
                /// 
                /// @param position The position of the pixel to draw.
                /// @param color Color struct, color to draw pixel
                void drawPixelV(Vector2 position, Color color);
                
                /// @brief It sets the color of a pixel.
                /// 
                /// @param dstPtr A pointer to the destination image.
                /// @param color The color to set the pixel to.
                /// @param format The format of the image.
                void setPixelColor(void *dstPtr, Color color, int format);
                
                /// @brief It gets the color of a pixel from a texture.
                /// 
                /// @param srcPtr Pointer to the source image data (CPU memory)
                /// @param format The format of the image.
                /// 
                /// @return A Color struct.
                Color getPixelColor(void *srcPtr, int format);

            protected:
            private:
                Vector2 _position;
                Color _color;
        };   
    }
}


#endif /* !PIXEL_HPP_ */
