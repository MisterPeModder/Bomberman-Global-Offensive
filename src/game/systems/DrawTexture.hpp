/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** DrawTexture
*/

#ifndef GAME_SYSTEMS_DRAWTEXTURE_HPP_
#define GAME_SYSTEMS_DRAWTEXTURE_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    /// Draw texture with a scale
    struct DrawTexture : public ecs::System {
        void run(ecs::SystemData data) override final;
    };

    /// Draw texture with a size. The texture is flipped when a size components is negative.
    struct DrawFlippedTexture : public ecs::System {
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif
