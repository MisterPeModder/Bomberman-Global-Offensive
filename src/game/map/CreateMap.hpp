/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** CreateMap
*/

#ifndef CREATEMAP_HPP_
#define CREATEMAP_HPP_

#include "game/map/Map.hpp"
#include "game/components/Color.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/Scale.hpp"
#include "game/systems/Model.hpp"

#include "raylib/model/Mesh.hpp"
#include "raylib/model/Model.hpp"

#include "ecs/join.hpp"
#include "ecs/World.hpp"
#include "ecs/resource/Timer.hpp"
#include "ecs/Storage.hpp"


/**
 * It creates a map
 * Start set the texture and the mesh and after set the texture at the mech
 *
 * Create after entities for the @param world, set by the @param map
 *
 * @param world The world that the entities will be added to.
 * @param map The map to create the entities from.
 */
void createMap(ecs::World &world,  game::map::Map &map);

#endif /* !CREATEMAP_HPP_ */
