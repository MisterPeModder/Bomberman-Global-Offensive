/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Rectangle
*/

#ifndef RAYLIB_SHAPE_RECTANGLE_HPP_
#define RAYLIB_SHAPE_RECTANGLE_HPP_

#include "raylib/core/Vector2.hpp"
#include "raylib/shapes/AShape.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace shapes
    {
        /// The Rectangle Class used to represent a 2d rectangle shape
        class Rectangle : public AShape {
          public:
            /// This function creates a rectangle from a position, a size and a color
            ///
            /// @param pos The position of the rectangle.
            /// @param size The size of the rectangle.
            /// @param color The color of the rectangle.
            Rectangle(raylib::core::Vector2f pos = {}, raylib::core::Vector2f size = {1.f, 1.f},
                raylib::core::Color color = raylib::core::Color::DEFAULT_COLOR);

            /// A constructor that takes a Rectangle as a parameter.
            ///
            /// @param other The rectangle to copy
            Rectangle(const Rectangle &other);

            /// This function creates a rectangle from a raylib Rectangle struct.
            ///
            /// @param rec raylib Rectangle.
            Rectangle(::Rectangle rec);

            /// The destructor for the Rectangle class.
            ~Rectangle();

            /// Copy an existing rectangle.
            ///
            /// @param other rectangle to copy.
            /// @return Rectangle& @b this.
            Rectangle &operator=(const Rectangle &other) = default;

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
            ::Rectangle getRaylibRectangle() const;

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
            void draw() const override;

            /// Draws a rectangle outline (or "wireframe") with the given color
            ///
            /// @param color The color of the rectangle.
            void drawLines() const;

            /// Draws a rectangle outline (or line) with extended parameters
            ///
            /// @param lineThick Thickness of the lines (in pixels)
            void drawLines(float lineThick) const;

            /// Draws a rectangle with rounded edges
            ///
            /// @param roundness The roundness of the corners in the range 0.0f - 1.0f.
            /// @param segments The number of segments to be used to draw the rounded
            /// edges (defaults to 30)
            /// @param color The color of the rectangle.
            void drawRounded(float roundness, float segments) const;

            /// Draws a rectangle with rounded corners outline
            ///
            /// @param roundness The roundness of the corners.
            /// @param segments The number of segments to be used to draw the rounded
            /// edges.
            /// @param lineThick The thickness of the lines.
            /// @param color The color of the lines
            void drawRoundedLines(float roundness, float segments, float lineThick) const;

            /// Checks if the rectangle is colliding with another rectangle.
            ///
            /// @param other The other rectangle to check collision with.
            ///
            /// @return A boolean value.
            bool checkCollision(Rectangle &other) const;

            /// Returns the collision rectangle between two rectangles.
            ///
            /// @param other The other rectangle to check collision with.
            ///
            /// @return A rectangle
            Rectangle getCollision(Rectangle &other) const;

          private:
            raylib::core::Vector2f _size;
        };
    } // namespace shapes
} // namespace raylib

#endif /* !RAYLIB_SHAPE_RECTANGLE_HPP_ */
