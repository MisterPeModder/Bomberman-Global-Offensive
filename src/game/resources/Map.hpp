/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Map
*/

#ifndef GAME_RESOURCES_MAP_HPP_
#define GAME_RESOURCES_MAP_HPP_

#include "ecs/resource/Resource.hpp"
#include "game/map/Map.hpp"

namespace game::resources
{
    struct Map : public ecs::Resource {
        game::map::Map &map;

        explicit Map(game::map::Map &pMap) : map(pMap) {}
    };
} // namespace game::resources

#endif /* !GAME_RESOURCES_MAP_HPP_ */
