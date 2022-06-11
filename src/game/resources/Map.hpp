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
    /// Game map resource.
    struct Map : public ecs::Resource {
        /// Reference to the map wrapped.
        game::map::Map &map;

        /// Construct a new Map resource.
        ///
        /// @param pMap @ref map.
        explicit Map(game::map::Map &pMap) : map(pMap) {}
    };
} // namespace game::resources

#endif /* !GAME_RESOURCES_MAP_HPP_ */
