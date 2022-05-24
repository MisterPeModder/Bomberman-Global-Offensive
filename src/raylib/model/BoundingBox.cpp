/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** BoundingBox
*/

#include "BoundingBox.hpp"

namespace raylib
{
    namespace model
    {
        BoundingBox::BoundingBox(const ::Model model)
        {
            ::BoundingBox box = GetModelBoundingBox(model);
            _min = box.min;
            _max = box.max;
        }

        BoundingBox::~BoundingBox()
        {
        }

        raylib::core::Vector3 BoundingBox::getMin() const
        {
            return _min;
        }

        raylib::core::Vector3 BoundingBox::getMax() const
        {
            return _max;
        }

        ::BoundingBox BoundingBox::asRaylib() const
        {
            return { _min.asRaylib(), _max.asRaylib() };
        }

        bool BoundingBox::checkCollision(const BoundingBox &other)
        {
            return CheckCollisionBoxes(this->asRaylib(), other.asRaylib());
        }
    }
}

