/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Cube
*/

#ifndef RAYLIB_SHAPE_CUBE_HPP_
#define RAYLIB_SHAPE_CUBE_HPP_

#include "AShape.hpp"
#include "raylib/core/Vector2.hpp"
#include "raylib/core/Vector3.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace shapes
    {
        /// 3D shape representing a cube.
        class Cube : public AShape {
          public:
            /// This function creates a cube from a position, a size and a color.
            ///
            /// @param position The position of the cube.
            /// @param size The size of the cube.
            /// @param color The color of the cube.
            Cube(Vector3 position = {}, Vector3 size = {}, Color color = Color{0, 0, 0, 0});

            /// A constructor that takes a Cube as a parameter.
            ///
            /// @param other The cube to copy
            Cube(Cube &other);

            /// The destructor for the Cube class.
            ~Cube() = default;

            /// Draw the cube.
            void draw() const override;

            /// Draw the wireframe of the cube.
            void drawWires() const;

            /// Set the Size of the cube.
            ///
            /// @param size new size of the cube.
            void setSize(Vector3 size);

            /// Get the Size of the cube.
            ///
            /// @return Vector3 size of the cube.
            Vector3 getSize() const;

          private:
            Vector3 _size;
        };
    } // namespace shapes
} // namespace raylib

#endif /* !RAYLIB_SHAPE_CUBE_HPP_ */
