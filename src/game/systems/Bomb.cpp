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
        auto now = std::chrono::steady_clock::now();

        for (auto [pos, bomb, id] : ecs::join(
                 data.getStorage<game::components::Position>(), data.getStorage<game::components::Bomb>(), entities)) {
            if (bomb.exploded || now - bomb.placedTime < bomb.explosionDelay)
                continue;
            std::vector<raylib::core::Vector2> explodablePositions;

            data.getResource<game::resources::Map>().map.fillExplodedPositions(
                explodablePositions, {pos.x, pos.z}, bomb.radius);
            bomb.exploded = true;
            // entities.erase(id);
        }
    }
} // namespace game::systems