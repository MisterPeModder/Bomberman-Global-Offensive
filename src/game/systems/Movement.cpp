/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Movement
*/

#include "Movement.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Timer.hpp"
#include "game/components/Position.hpp"
#include "game/components/Velocity.hpp"

namespace game
{
    void Movement::run(ecs::SystemData data)
    {
        float seconds = data.getResource<ecs::Timer>().elapsed();

        for (auto [pos, vel] : ecs::join(data.getStorage<Position>(), data.getStorage<Velocity>())) {
            // no friction here, just plain old perpertual motion
            pos.x += vel.x * seconds;
            pos.y += vel.y * seconds;
            pos.z += vel.z * seconds;
        }
        data.getResource<ecs::Timer>().reset();
    }
} // namespace game