/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Explosions
*/

#include "game/components/Explosion.hpp"
#include "Explosion.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "game/components/Color.hpp"
#include "logger/Logger.hpp"

namespace game::systems
{
    void ClearExplosions::run(ecs::SystemData data)
    {
        auto now = std::chrono::steady_clock::now();
        auto &entities = data.getResource<ecs::Entities>();

        for (auto [explosion, color, id] : ecs::join(data.getStorage<game::components::Explosion>(),
                 data.getStorage<game::components::Color>(), entities)) {
            auto timeElapsed = now - explosion.placedTime;
            if (timeElapsed > game::components::Explosion::EXPLOSION_DURATION)
                entities.kill(id);
            else {
                auto ratio = std::chrono::duration_cast<std::chrono::milliseconds>(timeElapsed).count()
                    / static_cast<float>(game::components::Explosion::EXPLOSION_DURATION.count());
                color.a = 255 * (1 - ratio);
            }
        }
    }
} // namespace game::systems
