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

                /// Sets the size of the shape
                ///
                /// @param size The new size of the shape
                void setSize(Vector3 size) { _size = size; }

                /// Gets the size of the shape
                ///
                /// @return The size of the shape
                Vector3 getSize() const { return _size; }

                /// Sets the position of the shape
                ///
                /// @param position The new position of the shape
                void setPosition(Vector3 position) { _position = position; }

                /// Gets the position of the shape
                ///
                /// @return The position of the shape
                Vector3 getPosition() const { return _position; }

            protected:
                Vector3 _size;
                Vector3 _position;
                Color _color;
        };
    }

}

#endif /* !RAYLIB_SHAPES_ASHAPE_HPP_ */
