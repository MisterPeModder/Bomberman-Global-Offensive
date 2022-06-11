/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** BoundingBox
*/

#ifndef RAYLIB_MODEL_BOUNDINGBOX_HPP_
#define RAYLIB_MODEL_BOUNDINGBOX_HPP_

extern "C"
{
#include <raylib.h>
}

#include "raylib/core/Vector3.hpp"

namespace raylib
{
    namespace model
    {
        class Model;
        /// The BoundingBox Class
        class BoundingBox {
          public:
            /// Deleted default constructor
            BoundingBox() = delete;

            /// BoundingBox constructor from a 3D model
            ///
            /// @param model the model to get the BoundingBox from
            BoundingBox(const Model &model);

            // Destructor
            ~BoundingBox() = default;

            /// Deleted copy constructor because it makes no sense
            BoundingBox(const BoundingBox &other) = delete;

            /// Deleted copy operator because it makes no sense
            BoundingBox &operator=(const BoundingBox &other) = delete;

            /// Gets the min point of the bounding box
            ///
            /// @return The min point of the bounding box
            raylib::core::Vector3f getMin() const;

            /// Gets the max point of the bounding box
            ///
            /// @return The max point of the bounding box
            raylib::core::Vector3f getMax() const;

            /// Checks collision with another bounding box
            ///
            /// @param other The other bounding box to check the collisions with
            ///
            /// @retval true if the two bounding boxes collides
            /// @retval false if the two bounding boxes doesn't collide
            bool checkCollision(const BoundingBox &other);

          private:
            /// Gets the C Raylib version of the bounding box
            ///
            /// @return The raylib version of the bounding box
            ::BoundingBox _asRaylib() const;

            raylib::core::Vector3f _min;
            raylib::core::Vector3f _max;
        };
    } // namespace model
} // namespace raylib

#endif /* !RAYLIB_MODEL_BOUNDINGBOX_HPP_ */
