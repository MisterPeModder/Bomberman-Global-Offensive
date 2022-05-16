/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Circle
*/

#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

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
        class Circle {
            public:

                /// This function is a constructor for the Circle class. It takes in the x,
                /// y, z, radius, and color of the circle and sets the values of the Circle
                /// class to those values
                /// 
                /// @param x The x coordinate of the center of the circle.
                /// @param y The y coordinate of the center of the circle.
                /// @param z The z-axis of the circle.
                /// @param radius The radius of the circle.
                /// @param color The color of the circle.
                Circle(float x = 0, float y = 0, float z = 0, float radius = 0, Color color = Color {0, 0, 0, 0});
                
                /// The destructor is called when the object is destroyed
                ~Circle();

                /// Draw a circle at the given x, y coordinates with the given radius and
                /// color.
                void draw();

                /// Draws a sector of a circle
                /// 
                /// @param startAngle The angle at which the sector starts.
                /// @param endAngle The angle at which the sector ends.
                /// @param segments The number of segments to use to draw the circle. More
                /// segments means a more detailed circle.
                /// @param color The color of the circle
                void drawSector(float startAngle, float endAngle, float segments, Color color);

                /// Draws a circle sector outline (or pie chart slice) using lines
                /// 
                /// @param startAngle The angle at which the sector starts.
                /// @param endAngle The angle in radians (0-2*PI) to end the sector at.
                /// @param segments The number of segments to use to draw the circle. More
                /// segments means a more detailed circle.
                /// @param color The color of the lines
                void drawSectorLines(float startAngle, float endAngle, float segments, Color color);

                /// Draw a circle with a gradient
                /// 
                /// @param color1 The color of the circle's center
                /// @param color2 The color of the outer circle
                void drawGradient(Color color1, Color color2);

                /// DrawCircleLines draws a circle with the given parameters
                /// 
                /// @param color Color of the circle to draw (it can be a Color struct or a
                /// number in hexadecimal format 0xRRGGBB)
                void drawLines(Color color);

                /// > Check if two circles are colliding
                /// 
                /// @param other The other circle to check for collision with.
                bool checkCollisions(Cirlce other);

                /// If the distance between the centers of the two circles is less than the
                /// sum of their radii, the circles are colliding
                /// 
                /// @param other The other rectangle to check against.
                bool checkCollisions(Rectangle other);
 

                /// Draw a circle in 3D space with a given rotation axis and angle
                /// 
                /// @param rotationAxis The axis of rotation.
                /// @param rotationAngle The angle of rotation in degrees.
                void draw3D(Vector3 rotationAxis, float rotationAngle);
            
                /// This function sets the position of the circle.
                /// 
                /// @param x The x position of the circle.
                /// @param y The y position of the circle.
                /// @param z The z-coordinate of the circle.
                void setPosition(float x, float y, float z = 0);
                
                /// `setRadius` is a function that takes a float as an argument and sets the
                /// value of the private variable `_radius` to the value of the argument
                /// 
                /// @param radius The radius of the circle.
                void setRadius(float radius);

                /// This function sets the color of the circle to the color passed in.
                /// 
                /// @param color The color of the circle.
                void setColor(Color color);

                /// It returns the position of the circle.
                /// 
                /// @return A Vector3 object.
                Vector3 getPosition();

                /// `getRadius()` returns the value of the private variable `_radius`
                /// 
                /// @return The radius of the circle.
                float getRadius();

                /// `getColor()` returns the color of the circle
                /// 
                /// @return The color of the circle.
                Color getColor();

            protected:
            private:
                float _x;
                float _y;
                float _z;
                float _radius;
                Color _color;
        };
    } // namespace shapes
} // namespace raylib


#endif /* !CIRCLE_HPP_ */
