/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** AShape
*/

#ifndef RAYLIB_SHAPES_ASHAPE_HPP_
#define RAYLIB_SHAPES_ASHAPE_HPP_

#include "raylib/core/Vector2.hpp"
#include "raylib/core/Vector3.hpp"

namespace raylib
{
    namespace shapes
    {
        class AShape {
          public:
            /// Virtual destructor
            virtual ~AShape();

            /// Draws the shape
            virtual void draw();

            /// Checks if a shape is in collision with another
            virtual bool checkCollision(AShape &);

            /// Sets the position of the shape
            ///
            /// @param position The new position of the shape
            inline void setPosition(Vector3 position) { _position = position; }

            /// Sets the position of the shape
            ///
            /// @param position The new position of the shape
            inline void setPosition(Vector2 position) { _position = {position.x, position.y, 0}; }

            /// Gets the position of the shape
            ///
            /// @return The position of the shape
            inline Vector3 getPosition() const { return _position; }

            /// Gets the position of the shape
            ///
            /// @return The position of the shape (2D)
            inline Vector2 getPosition2D() const { return {_position.x, _position.y}; }

            /// Sets the color of the shape
            ///
            /// @param color The new color of the shape
            inline void setColor(Color color) { _color = color; }

            /// Gets the color of the shape
            ///
            /// @return The color of the shape
            inline Color getColor() const { return _color; }

          protected:
            Vector3 _position;
            Color _color;
        };
    } // namespace shapes

} // namespace raylib

#endif /* !RAYLIB_SHAPES_ASHAPE_HPP_ */
