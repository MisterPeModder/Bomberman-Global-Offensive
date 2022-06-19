/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Hud
*/

#ifndef HUD_COMPONENTS_HPP_
#define HUD_COMPONENTS_HPP_

#include "Player.hpp"
#include "ecs/Component.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Identity.hpp"

namespace game::components
{
    /// Cube color component
    struct Hud : public ecs::Component {
        ///
        size_t nbBomb;
        size_t rangeBomb;
        float speed;
        bool inverted;
        bool slowness;
        Identity::Id idHud;

        Hud()
        {
            nbBomb = 0;
            rangeBomb = 0;
            speed = 0;
            inverted = 0;
            slowness = 0;
            idHud = 0;
        }
        Hud(ecs::SystemData data)
        {
            for (auto [player, id] :
                ecs::join(data.getStorage<game::components::Player>(), data.getStorage<game::components::Identity>())) {
                nbBomb = player.stats.bombLimit;
                rangeBomb = player.stats.bombRange;
                speed = player.stats.speed;
                inverted = player.stats.inverted;
                slowness = player.stats.slowness;
                idHud = id.getCurrentId();
            }
        }
    };
} // namespace game::components

#endif /*!HUD_COMPONENTS_HPP_*/
