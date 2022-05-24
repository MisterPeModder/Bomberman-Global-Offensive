/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Cylinder
*/

#ifndef RAYLIB_SHAPES_CYLINDER_HPP_
#define RAYLIB_SHAPES_CYLINDER_HPP_

#include "Cone.hpp"
#include "raylib/core/Vector3.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace shapes
    {
        /// 3D Cylinder shape, basically just a Cone with the same base and top radius
        class Cylinder : public Cone {
          public:
            /// This function creates a cylinder from a position, a radius, a height, a number of slices and a
            /// color.
            ///
            /// @param position The position of the center of the base.
            /// @param radius The radius of the cylinder.
            /// @param height The height of the cylinder.
            /// @param slices The number of slices of the cylinder, more slices mean more precise but more laggy.
            /// @param color The color of the cylinder.
            inline Cylinder(
                Vector3 position = {}, float radius = 0, float height = 0, int slices = 10, Color color = {0, 0, 0, 0})
                : Cone(position, radius, radius, height, slices, color){};

            /// Destroy the cylinder
            ~Cylinder() = default;

          private:
            using Cone::getBaseRadius;
            using Cone::getTopRadius;
            using Cone::isCylinder;
        };
    } // namespace shapes
} // namespace raylib

#endif /* !RAYLIB_SHAPES_CYLINDER_HPP_ */
