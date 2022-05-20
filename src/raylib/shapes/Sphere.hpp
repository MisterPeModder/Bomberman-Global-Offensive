/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Sphere
*/

#ifndef RAYLIB_SHAPE_SPHERE_HPP_
#define RAYLIB_SHAPE_SPHERE_HPP_

#include "AShape.hpp"
#include "raylib/core/Vector3.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace shapes
    {
        /// 3D shape representing a sphere.
        class Sphere : public AShape {
          public:
            /// This function creates a sphere from a position, a radius and a color.
            ///
            /// @param position The position of the center of the sphere.
            /// @param radius The radius of the sphere.
            /// @param color The color of the sphere.
            Sphere(Vector3 position = {}, float radius = 0, Color color = {0, 0, 0, 0});

            /// Destroy the sphere.
            ~Sphere() = default;

            /// Draw the sphere on the window.
            void draw() const;

            /// Draw the sphere on the window with specified parameters.
            ///
            /// @param rings number of rinds (horizontal)
            /// @param slices number of slices (vertical)
            void draw(int rings, int slices) const;

            /// Draw the sphere wireframe on the window.
            ///
            /// @param rings number of rinds (horizontal)
            /// @param slices number of slices (vertical)
            void drawWires(int rings, int slices) const;

            /// Gets the radius of the sphere.
            float getRadius();

            /// Sets the radius of the sphere.
            ///
            /// @param radius new radius of the sphere.
            void setRadius(float radius);

          private:
            float _radius;
        };
    } // namespace shapes
} // namespace raylib

#endif /* !RAYLIB_SHAPE_SPHERE_HPP_ */
