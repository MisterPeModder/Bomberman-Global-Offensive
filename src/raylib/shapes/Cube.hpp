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
            Cube(raylib::core::Vector3 position = {}, raylib::core::Vector3 size = {1, 1, 1},
                raylib::core::Color color = raylib::core::Color::DEFAULT_COLOR);

            /// A constructor that takes a Cube as a parameter.
            ///
            /// @param other The cube to copy
            Cube(Cube &other);

            /// The destructor for the Cube class.
            ~Cube() = default;

            /// Draw the cube.
            void draw() const override;

            /// Draw the cube at a particular location and with a particular size, ignoring the cube's position and size
            /// (and color) members
            ///
            /// @param position the position where the cube will be drawn
            /// @param size the size of the drawn cube
            /// @param color the color the the drawn cube
            void draw(raylib::core::Vector3 position, raylib::core::Vector3 size,
                raylib::core::Color color = raylib::core::Color::DEFAULT_COLOR) const;

            /// Draw the wireframe of the cube.
            void drawWires() const;

            /// Set the Size of the cube.
            ///
            /// @param size new size of the cube.
            void setSize(raylib::core::Vector3 size);

            /// Get the Size of the cube.
            ///
            /// @return Vector3 size of the cube.
            raylib::core::Vector3 getSize() const;

          private:
            raylib::core::Vector3 _size;
        };
    } // namespace shapes
} // namespace raylib

#endif /* !RAYLIB_SHAPE_CUBE_HPP_ */
