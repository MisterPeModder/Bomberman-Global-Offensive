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
#include "game/resources/GameClock.hpp"
#include "raylib/shapes/Sphere.hpp"

namespace game::systems
{
    void ExplodeBomb::run(ecs::SystemData data)
    {
        auto now = data.getResource<game::resources::GameClock>().getTime();

        for (auto [pos, bomb, id] : ecs::join(data.getStorage<game::components::Position>(),
                 data.getStorage<game::components::Bomb>(), data.getResource<ecs::Entities>())) {
            if (bomb.type == game::components::Bomb::Type::LandMine)
                continue;
            if (now - bomb.placedTime >= bomb.explosionDelay)
                bomb.explode(pos, data, id);
        }
    }
} // namespace game::systems
