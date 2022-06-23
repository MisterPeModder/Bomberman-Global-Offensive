/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** UpdateHud
*/

#include "UpdateHud.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Player.hpp"
#include "game/components/PlayerHud.hpp"

using namespace game::components;

namespace game::systems
{
    void UpdateHud::run(ecs::SystemData data)
    {
        for (auto [hud] : ecs::join(data.getStorage<PlayerHud>())) {
            for (auto [player, controlable] : ecs::join(data.getStorage<Player>(), data.getStorage<Controlable>())) {
                if (hud.owner == controlable.userId)
                    hud.update(data, player);
            }
        }
    }

} // namespace game::systems
