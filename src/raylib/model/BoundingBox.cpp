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

        ::BoundingBox BoundingBox::toRaylib() const
        {
            return { _min.toRaylib(), _max.toRaylib() };
        }

        bool BoundingBox::checkCollision(const BoundingBox &other)
        {
            return CheckCollisionBoxes(this->toRaylib(), other.toRaylib());
        }
    }
}

