
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Stun Grenade
*/

#include "Item.hpp"
#include "ecs/join.hpp"
#include "game/components/Color.hpp"
#include "game/components/Identity.hpp"
#include "game/components/Model.hpp"
#include "game/components/Player.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Size.hpp"
#include "game/components/Smoke.hpp"
#include "game/components/Sound.hpp"
#include "game/resources/AssetMap.hpp"
#include "raylib/core/Color.hpp"

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
        smokeGrenade.dropRate = 15;
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
                    .with<ModelReference>(
                        data.getStorage<ModelReference>(), data.getResource<resources::Models>().get("smoke_sphere"))
                    .with<Size>(data.getStorage<Size>(), 1.f, 1.f, 1.f)
                    .with<RotationAngle>(data.getStorage<RotationAngle>(), 0.0f)
                    .with<RotationAxis>(data.getStorage<RotationAxis>(), 0.f, 0.f, 0.f)
                    .with<components::Color>(data.getStorage<components::Color>(), 200, 200, 200, 220)
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
