/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Bomb
*/

#include "Bomb.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "game/components/Bomb.hpp"
#include "game/components/Destructible.hpp"
#include "game/components/Living.hpp"
#include "game/components/Position.hpp"
#include "game/components/Size.hpp"
#include "game/resources/Map.hpp"
#include "raylib/shapes/Sphere.hpp"

#include "Logger/Logger.hpp"

namespace game::systems
{
    void DrawBomb::run(ecs::SystemData data)
    {
        for (auto [pos, size, bomb, id] :
            ecs::join(data.getStorage<game::components::Position>(), data.getStorage<game::components::Size>(),
                data.getStorage<game::components::Bomb>(), data.getResource<ecs::Entities>())) {
            if (bomb.exploded)
                continue;
            raylib::shapes::Sphere(pos, size.x / 2.f, raylib::core::Color::GREEN).draw();
        }
    }

    void ExplodeBomb::run(ecs::SystemData data)
    {
        auto &entities = data.getResource<ecs::Entities>();
        auto &positions = data.getStorage<game::components::Position>();
        auto maybeDestructible = ecs::maybe(data.getStorage<game::components::Destructible>());
        auto maybeLiving = ecs::maybe(data.getStorage<game::components::Living>());
        auto now = std::chrono::steady_clock::now();
        game::map::Map &map = data.getResource<game::resources::Map>().map;

        for (auto [bombPos, bomb, id] : ecs::join(positions, data.getStorage<game::components::Bomb>(), entities)) {
            if (bomb.exploded || now - bomb.placedTime < bomb.explosionDelay)
                continue;
            std::vector<raylib::core::Vector2u> explodablePositions;

            map.fillExplodedPositions(explodablePositions,
                raylib::core::Vector2u(static_cast<unsigned int>(bombPos.x), static_cast<unsigned int>(bombPos.z)),
                bomb.radius);
            if (explodablePositions.empty())
                continue;
            // for (size_t i = 0; i < explodablePositions.size(); i++)
            //     Logger::logger.log(Logger::Severity::Debug, [&](auto &out) {
            //         out << "Add pos (" << explodablePositions[i].x << ", " << explodablePositions[i].y << ")";
            //     });
            for (auto [pos, destructible, living] : ecs::join(positions, maybeDestructible, maybeLiving)) {
                if ((!destructible && !living) || (destructible && destructible->destructed)
                    || (living && living->hp == 0))
                    continue;

                raylib::core::Vector2u pos2D = {static_cast<unsigned int>(pos.x), static_cast<unsigned int>(pos.z)};

                // Logger::logger.log(Logger::Severity::Debug,
                //     [&](auto &out) { out << "Test pos (" << pos2D.x << ", " << pos2D.y << ")"; });
                if (std::find(explodablePositions.begin(), explodablePositions.end(), pos2D)
                    == explodablePositions.end())
                    continue;
                if (destructible)
                    destructible->destructed = true;
                if (living)
                    Logger::logger.log(Logger::Severity::Debug, "Die");
                // living->hp--;
                map.getElement(pos2D) = game::map::Map::Element::Empty;
            }
            bomb.exploded = true;
            // entities.erase(id);
        }
    }
} // namespace game::systems