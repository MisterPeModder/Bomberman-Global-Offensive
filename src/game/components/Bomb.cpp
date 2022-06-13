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
    void Bomb::explode(const Position &bombPos, ecs::SystemData data)
    {
        if (this->exploded)
            return;
        this->exploded = true;
        /// Retrieve storages
        auto &positions = data.getStorage<Position>();
        auto maybeDestructible = ecs::maybe(data.getStorage<Destructible>());
        auto maybeLiving = ecs::maybe(data.getStorage<Living>());
        auto maybeBomb = ecs::maybe(data.getStorage<Bomb>());

        /// Retrieve exploded cells
        game::map::Map &map = data.getResource<game::resources::Map>().map;
        std::vector<raylib::core::Vector2u> explodedPositions;

        map.fillExplodedPositions(explodedPositions,
            raylib::core::Vector2u(static_cast<unsigned int>(bombPos.x), static_cast<unsigned int>(bombPos.z)),
            this->radius);
        if (explodedPositions.empty())
            return;

        /// Test for destructible and living entities if they are in an exploded cell.
        for (auto [pos, destructible, living, bomb] : ecs::join(positions, maybeDestructible, maybeLiving, maybeBomb)) {
            /// Do not care about dead, destroyed or exploded entities
            if ((!destructible && !living && !bomb) || (destructible && destructible->destroyed)
                || (living && living->hp == 0) || (bomb && bomb->exploded))
                continue;

            raylib::core::Vector2u pos2D = {static_cast<unsigned int>(pos.x), static_cast<unsigned int>(pos.z)};

            if (std::find(explodedPositions.begin(), explodedPositions.end(), pos2D) == explodedPositions.end())
                continue;
            map.getElement(pos2D) = game::map::Map::Element::Empty;
            if (destructible)
                destructible->destroyed = true;
            if (living)
                Logger::logger.log(Logger::Severity::Debug, "Living entity hit by a bomb"); // living->hp--;
            if (bomb)
                bomb->explode(pos, data);
        }
    }
} // namespace game::components
