/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** AiControlable
*/

#include "AiControlable.hpp"
#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include "ecs/System.hpp"

#include "raylib/core/Vector2.hpp"

#include <deque>

namespace game::components
{
    void AiControlable::pathFind(raylib::core::Vector2f pos, ecs::Entity self, ecs::SystemData data)
    {
        // no pathing at the moment :(
        (void)self;
        (void)data;
        this->path.push_back(pos);
    }

} // namespace game::components
