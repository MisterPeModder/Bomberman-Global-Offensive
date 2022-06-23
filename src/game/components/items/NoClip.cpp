
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** No clip
*/

#include "Item.hpp"
#include "game/components/Player.hpp"
#include "game/components/Sound.hpp"

namespace game::components
{
    Item Item::NoClip()
    {
        Item noClip;

        noClip.type = Item::Type::Activable;
        noClip.identifier = Item::Identifier::NoClip;
        noClip.maxStack = 1;
        noClip.name = "Wall Pass";
        noClip.duration = std::chrono::milliseconds(3000);
        noClip.dropRate = 30;
        noClip.onApply = [](ecs::Entity placer, ecs::SystemData data) {
            auto &player = data.getStorage<Player>()[placer.getId()];

            if (player.stats.clipState != Player::Stats::ClipState::Default)
                return false;
            game::components::Sound::playSound(data, "no_clip");
            player.stats.clipState = Player::Stats::ClipState::NoClip;
            return true;
        };
        noClip.onTimedOut = [](ecs::Entity placer, ecs::SystemData data) {
            data.getStorage<Player>()[placer.getId()].stats.clipState = Player::Stats::ClipState::WaitNoCollision;
        };
        return noClip;
    }
} // namespace game::components
