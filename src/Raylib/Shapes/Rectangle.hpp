/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Rectangle
*/

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include "Raylib/Core/Vector2.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace shapes
    {
        class Rectangle {
          public:
            /// @brief This function creates a rectangle object with the given parameters
            ///
            /// @param posX The X position of the rectangle.
            /// @param posY The Y position of the rectangle.
            /// @param width The width of the rectangle.
            /// @param height The height of the rectangle.
            Rectangle(float posX = 0, float posY = 0, float width = 0, float height = 0);

            /// @brief `raylib::Shapes::Rectangle::Rectangle(Vector2 pos, float width, float height)`
            ///
            /// This is a constructor for the `Rectangle` class. It takes a `Vector2` object
            /// called `pos` and two floategers called `width` and `height`
            ///
            /// @param pos The position of the rectangle.
            /// @param width The width of the rectangle
            /// @param height The height of the rectangle.
            Rectangle(Vector2 position, float width = 0, float height = 0);

            Rectangle(::Rectangle rec);
            /// @brief Destructor
            ~Rectangle();

            /// @brief Draws a rectangle
            ///
            /// @param posX The x position of the rectangle
            /// @param posY The Y position of the rectangle
            /// @param width The width of the rectangle
            /// @param height The height of the rectangle
            /// @param color The color of the rectangle
            void drawRectangle(float posX, float posY, float width, float height, Color color);

            /// @brief Draws a rectangle defined by its bottom-left corner and size
            ///
            /// @param position The position of the rectangle.
            /// @param size The size of the rectangle.
            /// @param color The color of the rectangle.
            void drawRectangleV(Vector2 position, Vector2 size, Color color);

            /// @brief Draws a rectangle.
            ///
            /// @param rec The rectangle to draw
            /// @param color Color struct
            void drawRectangleRec(Rectangle rec, Color color);

            /// @brief Draws a rectangle outline
            ///
            /// @param posX The x position of the rectangle
            /// @param posY The Y position of the rectangle
            /// @param width The width of the rectangle
            /// @param height The height of the rectangle.
            /// @param color The color of the rectangle.
            void drawRectangleLines(float posX, float posY, float width, float height, Color color);

            /// @brief It draws a rectangle with lines.
            ///
            /// @param pos The position of the rectangle
            /// @param width The width of the rectangle
            /// @param height The height of the rectangle
            /// @param color The color of the rectangle.
            void drawRectangleLines(Vector2 pos, float width, float height, Color color);

            /// @brief Draws a rectangle outline with extended parameters
            ///
            /// @param rec The rectangle to draw
            /// @param lineThick Thickness of the lines
            /// @param color The color of the rectangle
            void drawRectangleLinesEx(Rectangle rec, float lineThick, Color color);

            /// @brief Draws a rectangle with rounded edges
            ///
            /// @param rec The rectangle to draw
            /// @param roundness The roundness of the rectangle's corners.
            /// @param segments The number of segments to use when drawing the rounded corners.
            /// @param color The color of the rectangle
            void drawRectangleRounded(Rectangle rec, float roundness, float segments, Color color);

            /// @brief Draws a rectangle with rounded edges (Vector version)
            ///
            /// @param rec The rectangle to draw
            /// @param roundness The roundness of the rectangle's corners.
            /// @param segments The number of segments to use when drawing the rounded corners.
            /// @param lineThick Thickness of the lines used to draw the rectangle
            /// @param color The color of the rectangle
            void drawRectangleRoundedLines(Rectangle rec, float roundness, float segments, float lineThick, Color color);

            /// @brief Checks collision between two rectangles.
            ///
            /// @param rec1 The first rectangle to check.
            /// @param rec2 The second rectangle to check for collision.
            ///
            /// @return A boolean value.
            bool checkCollisionRecs(Rectangle rec1, Rectangle rec2);

            /// @brief It returns a rectangle that represents the collision area between two
            /// rectangles.
            ///
            /// @param rec1 The first rectangle to check for collision.
            /// @param rec2 The second rectangle to check for collision.
            ///
            /// @return A raylib::Shapes::Rectangle
            Rectangle getCollisionRec(Rectangle rec1, Rectangle rec2);

            ::Rectangle C_rectangle();

          protected:
          private:
            Vector2 _position;
            float _width;
            float _height;
        };
    } // namespace shapes
} // namespace raylib

#endif /* !RECTANGLE_HPP_ */
