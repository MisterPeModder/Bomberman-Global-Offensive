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
#include "raylib/shapes/Sphere.hpp"

namespace game::systems
{
    void DrawBomb::run(ecs::SystemData data)
    {
        (void)data;
        // for (auto [pos, size, bomb] : ecs::join(data.getStorage<game::components::Position>(),
        //          data.getStorage<game::components::Size>(), data.getStorage<game::components::Bomb>())) {
        //     (void)bomb;
        //     raylib::shapes::Sphere(pos, size.x / 2.f, raylib::core::Color::GREEN).draw();
        // }
    }

    void ExplodeBomb::run(ecs::SystemData data)
    {
        auto now = std::chrono::steady_clock::now();

        for (auto [pos, bomb, id] : ecs::join(data.getStorage<game::components::Position>(),
                 data.getStorage<game::components::Bomb>(), data.getResource<ecs::Entities>())) {
            if (now - bomb.placedTime >= bomb.explosionDelay)
                bomb.explode(pos, data, id);
        }
    }
} // namespace game::systems
