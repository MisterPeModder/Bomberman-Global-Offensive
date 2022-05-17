/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Rectangle
*/

#ifndef RAYLIB_SHAPE_RECTANGLE_HPP_
#define RAYLIB_SHAPE_RECTANGLE_HPP_

#include "raylib/core/Vector2.hpp"

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
            /// This function creates a rectangle with a position, width, height, and
            /// color
            ///
            /// @param posX The x position of the rectangle.
            /// @param posY The Y position of the rectangle.
            /// @param width The width of the rectangle.
            /// @param height The height of the rectangle.
            /// @param color The color of the rectangle.
            Rectangle(float posX = 0, float posY = 0, float width = 0, float height = 0, Color color = {0, 0, 0, 0});

            /// A constructor that takes a Rectangle as a parameter.
            ///
            /// @param rec The rectangle to copy
            Rectangle(Vector2 position, float width = 0, float height = 0, Color color = {0, 0, 0, 0});

            /// This function creates a rectangle with a position, width, height, and
            /// color
            ///
            /// @param pos The position of the rectangle.
            /// @param width The width of the rectangle.
            /// @param height The height of the rectangle.
            /// @param color The color of the rectangle.
            Rectangle(::Rectangle rec);

            /// The destructor for the Rectangle class.
            ~Rectangle();

            /// "Return a C++ Rectangle object with the same position and dimensions as
            /// this Rectangle object."
            ///
            /// The first line of the function is a return statement. It returns a C++
            /// Rectangle object. The return statement is followed by a pair of curly
            /// braces. The curly braces contain a list of arguments. The arguments are
            /// separated by commas. The arguments are the same arguments that are
            /// passed to the constructor of the C++ Rectangle class
            ///
            /// @return A rectangle object.
            ::Rectangle C_rectangle();

            /// `void Rectangle::draw() { DrawRectangleRec(this->C_rectangle(), _color);
            /// }`
            ///
            /// The function `draw()` is a member function of the class `Rectangle`. It
            /// is a public function, so it can be called from outside the class. It
            /// takes no arguments and returns nothing. It calls the function
            /// `DrawRectangleRec()` from the raylib library, which takes two arguments:
            /// a `Rectangle` and a `Color`. The first argument is the `Rectangle` that
            /// is a member of the class `Rectangle`. The second argument is the `Color`
            /// that is a member of the class `Rectangle`
            void draw();

            /// Draws a rectangle outline (or "wireframe") with the given color
            ///
            /// @param color The color of the rectangle.
            void drawLines(Color color);

            /// Draws a rectangle outline (or line) with extended parameters
            ///
            /// @param lineThick Thickness of the lines (in pixels)
            /// @param color The color of the rectangle.
            void drawLinesEx(float lineThick, Color color);

            /// Draws a rectangle with rounded edges
            ///
            /// @param roundness The roundness of the corners in the range 0.0f - 1.0f.
            /// @param segments The number of segments to be used to draw the rounded
            /// edges (defaults to 30)
            /// @param color The color of the rectangle.
            void drawRounded(float roundness, float segments, Color color);

            /// Draws a rectangle with rounded corners outline
            ///
            /// @param roundness The roundness of the corners.
            /// @param segments The number of segments to be used to draw the rounded
            /// edges.
            /// @param lineThick The thickness of the lines.
            /// @param color The color of the lines
            void drawRoundedLines(float roundness, float segments, float lineThick, Color color);

            /// It checks if the rectangle is colliding with another rectangle.
            ///
            /// @param other The other rectangle to check collision with.
            ///
            /// @return A boolean value.
            bool checkCollision(Rectangle other);

            /// It returns the collision rectangle between two rectangles.
            ///
            /// @param other The other rectangle to check collision with.
            ///
            /// @return A rectangle
            Rectangle getCollision(Rectangle other);

            /// `Color Rectangle::getColor()`
            ///
            /// This function returns a `Color` object. It is a member of the
            /// `Rectangle` class
            ///
            /// @return The color of the rectangle.

            Color getColor();

            /// This function returns the position of the rectangle
            ///
            /// @return The position of the rectangle.
            Vector2 getPosition();

            /// This function returns the width of the rectangle
            ///
            /// @return The width of the rectangle.
            float getWidth();

            /// `getHeight()` returns the height of the rectangle
            ///
            /// @return The height of the rectangle
            float getHeight();

            /// This function sets the position of the rectangle
            ///
            /// @param position The position of the rectangle.
            void setPosition(Vector2 position);

            /// Sets the color of the rectangle to the given color.
            ///
            /// @param color The color of the rectangle.
            void setColor(Color color);

            /// This function sets the width and height of the rectangle.
            ///
            /// @param width The width of the rectangle.
            /// @param height The height of the rectangle.
            void setSize(float width, float height);

          protected:
          private:
            Vector2 _position;
            float _width;
            float _height;
            Color _color;
        };
    } // namespace shapes
} // namespace raylib

#endif /* !RAYLIB_SHAPE_RECTANGLE_HPP_ */
