/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Cylinder
*/

#ifndef RAYLIB_SHAPES_CONE_HPP_
#define RAYLIB_SHAPES_CONE_HPP_

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
        /// 3D Cone shape. Can be used as a cylinder when base and top radius are equal (See Cylinder shape).
        class Cone : public AShape {
          public:
            /// This function creates a cone from a position, a base and top radius, a height, a number of slices and a
            /// color.
            ///
            /// @param position The position of the center of the base.
            /// @param radiusBase The radius of the base.
            /// @param radiusTop The radius of the top.
            /// @param height The height of the cone.
            /// @param slices The number of slices of the cone, more slices mean more precise but more laggy.
            /// @param color The color of the cone.
            Cone(raylib::core::Vector3 position = {}, float radiusBase = 1, float radiusTop = 0, float height = 1,
                int slices = 10, raylib::core::Color color = raylib::core::Color::DEFAULT_COLOR);

            /// Destroy the cone
            ~Cone() = default;

            /// Draw the cone
            void draw() const override;

            /// Draw the cone wires
            void drawWires() const;

            /// Sets bith base and top radius to the same radius (making the cone a cylinder)
            ///
            /// @param radius new radius of the base and top.
            void setRadius(float radius);

            /// Sets the base/top radius.
            ///
            /// @param base new base radius.
            /// @param top new top radius.
            virtual void setRadius(float base, float top);

            /// Gets the base radius.
            ///
            /// @return float base radius.
            float getBaseRadius() const;

            /// Gets the top radius.
            ///
            /// @return float top radius.
            float getTopRadius() const;

            /// Sets the height.
            ///
            /// @param height new height.
            ///
            void setHeight(float height);

            /// Gets the height.
            ///
            /// @return float height.
            float getHeight() const;

            /// Sets the number of slices.
            ///
            /// @param slices new number of slices.
            ///
            void setSlices(int slices);

            /// Gets the number of slices
            ///
            /// @return int number of slices
            int getSlices() const;

            /// Test if the cone is a cylinder (if base and top radius are equals).
            bool isCylinder() const;

          private:
            float _radiusBase;
            float _radiusTop;
            float _height;
            int _slices;
        };
    } // namespace shapes
} // namespace raylib

#endif /* !RAYLIB_SHAPES_CONE_HPP_ */
