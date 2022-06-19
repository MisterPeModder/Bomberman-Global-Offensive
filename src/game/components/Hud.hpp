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

        Hud(Player owner, Identity id)
            : nbBomb(owner.stats.bombLimit), rangeBomb(owner.stats.bombRange), speed(owner.stats.speed),
              inverted(owner.stats.inverted), slowness(owner.stats.slowness), idHud(id.getCurrentId())
        {
        }
    };
} // namespace game::components

#endif /*!HUD_COMPONENTS_HPP_*/
