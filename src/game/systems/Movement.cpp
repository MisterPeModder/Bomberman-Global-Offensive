/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Movement
*/

#include "Movement.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "game/components/Position.hpp"
#include "game/components/Velocity.hpp"
#include "game/resources/GameClock.hpp"

using namespace game::components;

namespace game::systems
{
    void Movement::run(ecs::SystemData data)
    {
        float seconds = data.getResource<game::resources::GameClock>().elapsedSeconds();

        for (auto [pos, vel] : ecs::join(data.getStorage<Position>(), data.getStorage<Velocity>())) {
            // no friction here, just plain old perpertual motion
            pos.x += vel.x * seconds;
            pos.y += vel.y * seconds;
            pos.z += vel.z * seconds;
        }
    }
} // namespace game::systems
