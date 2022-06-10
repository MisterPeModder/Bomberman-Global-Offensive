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

namespace game
{
    struct Collidable : public ecs::Component {};
    SET_COMPONENT_STORAGE(Marker, ecs::MarkerStorage);

    struct Wall : public ecs::Component {};
    SET_COMPONENT_STORAGE(Marker, ecs::MarkerStorage);
} // namespace game

#endif /* !GAME_COMPONENTS_COLLIDABLE_HPP_ */
