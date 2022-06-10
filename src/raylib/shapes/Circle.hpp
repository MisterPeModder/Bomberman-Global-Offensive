/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Circle
*/

#ifndef RAYLIB_SHAPE_CIRCLE_HPP_
#define RAYLIB_SHAPE_CIRCLE_HPP_

#include "AShape.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace shapes
    {
        class Rectangle;

        /// The Circle Class used to represent a 2d circle shape
        class Circle : public AShape {
          public:
            /// This function is a constructor for the Circle class. It takes in the position (2D), radius, and color of
            /// the circle and sets the values of the Circle class to those values
            ///
            /// @param pos The position of the center of the circle.
            /// @param radius The radius of the circle.
            /// @param color The color of the circle.
            Circle(raylib::core::Vector2 pos, float radius = 1.f,
                raylib::core::Color color = raylib::core::Color::DEFAULT_COLOR);

            /// The destructor is called when the object is destroyed
            ~Circle();

            /// Draw a circle at the given x, y coordinates with the given radius and
            /// color.
            void draw() const override;

            /// Draws a sector of a circle
            ///
            /// @param startAngle The angle at which the sector starts.
            /// @param endAngle The angle at which the sector ends.
            /// @param segments The number of segments to use to draw the circle. More
            /// segments means a more detailed circle.
            /// @param color The color of the circle
            void drawSector(float startAngle, float endAngle, int segments) const;

            /// Draws a circle sector outline (or pie chart slice) using lines
            ///
            /// @param startAngle The angle at which the sector starts.
            /// @param endAngle The angle in radians (0-2*PI) to end the sector at.
            /// @param segments The number of segments to use to draw the circle. More
            /// segments means a more detailed circle.
            /// @param color The color of the lines
            void drawSectorLines(float startAngle, float endAngle, int segments) const;

            /// Draw a circle with a gradient
            ///
            /// @param color1 The color of the circle's center
            /// @param color2 The color of the outer circle
            void drawGradient(raylib::core::Color color1, raylib::core::Color color2) const;

            /// DrawCircleLines draws a circle with the given parameters
            ///
            /// @param color Color of the circle to draw (it can be a Color struct or a
            /// number in hexadecimal format 0xRRGGBB)
            void drawLines() const;

            /// Check if two circles are colliding
            ///
            /// @param other The other circle to check for collision with.
            bool checkCollisions(const Circle &other) const;

            /// If the distance between the centers of the two circles is less than the
            /// sum of their radii, the circles are colliding
            ///
            /// @param other The other rectangle to check against.
            bool checkCollisions(const raylib::shapes::Rectangle &other) const;

            /// Draw a circle in 3D space with a given rotation axis and angle
            ///
            /// @param rotationAxis The axis of rotation.
            /// @param rotationAngle The angle of rotation in degrees.
            void draw3D(raylib::core::Vector3 rotationAxis, float rotationAngle) const;

            /// `setRadius` is a function that takes a float as an argument and sets the
            /// value of the private variable `_radius` to the value of the argument
            ///
            /// @param radius The radius of the circle.
            void setRadius(float radius);

            /// `getRadius()` returns the value of the private variable `_radius`
            ///
            /// @return The radius of the circle.
            float getRadius() const;

          private:
            float _radius;
        };
    } // namespace shapes
} // namespace raylib

#endif /* !RAYLIB_SHAPE_CIRCLE_HPP_ */
