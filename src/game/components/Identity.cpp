/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Identity
*/

#include "Identity.hpp"

namespace game::components
{
    Identity::Id Identity::_currentId = 0;

    Identity::Identity() : id(_currentId++) {}

    Identity::Id Identity::getCurrentId() { return _currentId; }
} // namespace game::components
