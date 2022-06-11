/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Bomb
*/

#include "Bomb.hpp"
#include "Destructible.hpp"
#include "Living.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "game/map/Map.hpp"
#include "game/resources/Map.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Vector2.hpp"

namespace game::components
{
    void Bomb::explode(ecs::Entity id, const Position &pos, ecs::SystemData data)
    {
        if (this->exploded)
            return;
        /// Retrieve storages
        auto &positions = data.getStorage<Position>();
        auto maybeDestructible = ecs::maybe(data.getStorage<game::components::Destructible>());
        auto maybeLiving = ecs::maybe(data.getStorage<game::components::Living>());

        /// Retrieve exploded cells
        game::map::Map &map = data.getResource<game::resources::Map>().map;
        std::vector<raylib::core::Vector2u> explodedPositions;

        map.fillExplodedPositions(explodedPositions,
            raylib::core::Vector2u(static_cast<unsigned int>(pos.x), static_cast<unsigned int>(pos.z)), this->radius);
        if (explodedPositions.empty())
            return;

        /// Test for destructible and living entities if they are in an exploded cell.
        for (auto [pos, destructible, living] : ecs::join(positions, maybeDestructible, maybeLiving)) {
            /// Do not care about dead or destroyed entities
            if ((!destructible && !living) || (destructible && destructible->destroyed) || (living && living->hp == 0))
                continue;

            raylib::core::Vector2u pos2D = {static_cast<unsigned int>(pos.x), static_cast<unsigned int>(pos.z)};

            if (std::find(explodedPositions.begin(), explodedPositions.end(), pos2D) == explodedPositions.end())
                continue;
            if (destructible)
                destructible->destroyed = true;
            if (living)
                Logger::logger.log(Logger::Severity::Debug, "Living entity hit by a bomb"); // living->hp--;
            map.getElement(pos2D) = game::map::Map::Element::Empty;
        }
        this->exploded = true;
    }
} // namespace game::components