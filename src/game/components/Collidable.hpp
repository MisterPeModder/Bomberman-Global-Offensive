/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Collidable
*/

#ifndef GAME_COMPONENTS_COLLIDABLE_HPP_
#define GAME_COMPONENTS_COLLIDABLE_HPP_

#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"

namespace game::components
{
    struct Collidable : public ecs::Component {};
    SET_COMPONENT_STORAGE(Collidable, ecs::MarkerStorage);

    struct Wall : public ecs::Component {};
    SET_COMPONENT_STORAGE(Wall, ecs::MarkerStorage);

    struct Player : public ecs::Component {};
    SET_COMPONENT_STORAGE(Player, ecs::MarkerStorage);
} // namespace game::components

#endif /* !GAME_COMPONENTS_COLLIDABLE_HPP_ */
