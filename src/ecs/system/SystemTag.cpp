/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - System group tag
*/

#include "ecs/system/SystemTag.hpp"

#include <algorithm>

namespace ecs
{
    SystemTag::SystemTag() : _types() {}

    SystemTag &SystemTag::add(SystemTag const &source)
    {
        for (auto &type : source._types) {
            if (std::find(this->_types.cbegin(), this->_types.cend(), type) != this->_types.cbegin())
                this->_types.push_back(type);
        }
        return *this;
    }
} // namespace ecs
