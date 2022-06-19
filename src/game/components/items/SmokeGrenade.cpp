
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Stun Grenade
*/

#include "Item.hpp"
#include "ecs/join.hpp"
#include "game/components/Identity.hpp"
#include "game/components/Player.hpp"
#include "game/components/Position.hpp"
#include "game/components/Smoke.hpp"
#include "game/components/Sound.hpp"

namespace game::components
{
    Item Item::SmokeGrenade()
    {
        Item smokeGrenade;

        smokeGrenade.type = Item::Type::Activable;
        smokeGrenade.identifier = Item::Identifier::SmokeGrenade;
        smokeGrenade.maxStack = 0;
        smokeGrenade.name = "Smoke Grenade";
        smokeGrenade.duration = std::chrono::milliseconds(7000);
        smokeGrenade.dropRate = 65;
        smokeGrenade.onApply = [](ecs::Entity placer, ecs::SystemData data) {
            auto &positions = data.getStorage<Position>();
            auto &smokes = data.getStorage<Smoke>();

            /// Don't activate two smokes at a time.
            if (smokes.size() > 0)
                return false;

            game::components::Sound::playSound(data, "smoke");

            /// Place a smoke on all ennemies.
            for (auto [pos, player, id, entity] : ecs::join(positions, data.getStorage<Player>(),
                     data.getStorage<Identity>(), data.getResource<ecs::Entities>())) {
                (void)player;
                if (entity.getId() == placer.getId())
                    continue;
                data.getResource<ecs::Entities>()
                    .builder()
                    .with<Smoke>(smokes, id.id)
                    .with<Position>(positions, pos)
                    .build();
            }
            return true;
        };
        smokeGrenade.onTimedOut = [](ecs::Entity placer, ecs::SystemData data) {
            (void)placer;
            auto &entities = data.getResource<ecs::Entities>();
            /// Remove all smokes
            for (auto [smoke, entity] : ecs::join(data.getStorage<Smoke>(), entities)) {
                (void)smoke;
                entities.kill(entity);
            }
        };
        return smokeGrenade;
    }
} // namespace game::components
