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
        class BoundingBox {
          public:
            BoundingBox(const ::Model model);

            ~BoundingBox();

            raylib::core::Vector3 getMin() const;

            raylib::core::Vector3 getMax() const;

            bool checkCollision(const BoundingBox &other);

            ::BoundingBox toRaylib() const;

          protected:
          private:
            raylib::core::Vector3 _min;
            raylib::core::Vector3 _max;
        };
    }
}

#endif /* !RAYLIB_MODEL_BOUNDINGBOX_HPP_ */
