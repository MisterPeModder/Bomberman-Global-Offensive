/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Smoke
*/

#include "Smoke.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "game/components/Identity.hpp"
#include "game/components/Position.hpp"
#include "game/components/Smoke.hpp"
#include "raylib/shapes/Sphere.hpp"

namespace game::systems
{
    void MoveSmoke::run(ecs::SystemData data)
    {
        auto &positions = data.getStorage<game::components::Position>();

        for (auto [pos, smoke] : ecs::join(positions, data.getStorage<game::components::Smoke>())) {
            for (auto [ownerPos, id] : ecs::join(positions, data.getStorage<game::components::Identity>())) {
                if (id.id != smoke.owner)
                    continue;
                pos = ownerPos;
                break;
            }
        }
    }
} // namespace game::systems
