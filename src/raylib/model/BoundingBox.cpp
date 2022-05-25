/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** BoundingBox
*/

#include "BoundingBox.hpp"
#include "Model.hpp"

namespace raylib
{
    namespace model
    {
        BoundingBox::BoundingBox(const Model &model)
        {
            ::BoundingBox box = GetModelBoundingBox(model.asRaylib());
            _min = box.min;
            _max = box.max;
        }

        raylib::core::Vector3 BoundingBox::getMin() const { return _min; }

        raylib::core::Vector3 BoundingBox::getMax() const { return _max; }

        ::BoundingBox BoundingBox::_asRaylib() const { return {_min.asRaylib(), _max.asRaylib()}; }

        bool BoundingBox::checkCollision(const BoundingBox &other)
        {
            return CheckCollisionBoxes(this->_asRaylib(), other._asRaylib());
        }
    } // namespace model
} // namespace raylib
