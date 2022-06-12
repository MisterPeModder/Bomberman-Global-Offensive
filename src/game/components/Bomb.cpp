/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Bomb
*/

#include "Bomb.hpp"
#include <cmath>
#include "Destructible.hpp"
#include "Living.hpp"
#include "Size.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
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
        auto &sizes = data.getStorage<Size>();
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
        for (auto [pos, size, destructible, living, bomb] :
            ecs::join(positions, sizes, maybeDestructible, maybeLiving, maybeBomb)) {
            /// Do not care about dead, destroyed or exploded entities
            if ((!destructible && !living && !bomb) || (destructible && destructible->destroyed)
                || (living && living->hp == 0) || (bomb && bomb->exploded))
                continue;

            raylib::core::Vector2u roundedPos2D = {
                static_cast<unsigned int>(std::round(pos.x)), static_cast<unsigned int>(std::round(pos.z))};

            if (std::find(explodedPositions.begin(), explodedPositions.end(), roundedPos2D) == explodedPositions.end()
                && (!living || !explodeLiving(pos, size, roundedPos2D, explodedPositions)))
                continue;

            if (living) {
                explodeLiving(pos, size, roundedPos2D, explodedPositions);
                Logger::logger.log(Logger::Severity::Debug, "Living entity hit by a bomb"); // living->hp--;
            }
            if (destructible) {
                map.getElement(roundedPos2D) = game::map::Map::Element::Empty;
                destructible->destroyed = true;
            }
            if (bomb)
                bomb->explode(pos, data);
        }
    }

    bool Bomb::explodeLiving(raylib::core::Vector3f pos, raylib::core::Vector3f size,
        raylib::core::Vector2u roundedPos2D, const std::vector<raylib::core::Vector2u> &explodedPositions) const
    {
        static float limit = 0.45f;
        raylib::core::Vector2f centerDelta = {
            pos.x - static_cast<float>(roundedPos2D.x), pos.z - static_cast<float>(roundedPos2D.y)};
        raylib::core::Vector2f overtake = {abs(centerDelta.x) + size.x * 0.5f, abs(centerDelta.y) + size.z * 0.5f};

        // Logger::logger.log(Logger::Severity::Debug, [&](auto &out) {
        //     out << "Living delta  (" << roundedPos2D.x << ", " << roundedPos2D.y << ") - (" << pos.x << ", " << pos.z
        //         << ") = (" << centerDelta.x << ", " << centerDelta.y << ") : overtake of (" << overtake.x << ", "
        //         << overtake.y << ")";
        // });

        if (overtake.x < 0.5f && overtake.y < 0.5f)
            return false;
        // Logger::logger.log(Logger::Severity::Debug, [&](auto &out) {
        //     out << "Living overtake the cell (" << (overtake.x - 0.5f) / size.x << "%, " << (overtake.y - 0.5f) /
        //     size.z
        //         << ")";
        // });

        if ((overtake.x - 0.5f) < size.x * limit && (overtake.y - 0.5f) < size.z * limit)
            return false;
        // raylib::core::Vector2u otherPos;

        Logger::logger.log(Logger::Severity::Debug, [&](auto &out) { out << "Living might be in an other cell"; });

        return false;
    }
} // namespace game::components
