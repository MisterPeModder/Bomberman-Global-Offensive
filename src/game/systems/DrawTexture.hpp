/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** DrawTexture
*/

#ifndef GAME_SYSTEMS_DRAWTEXTURE_HPP_
#define GAME_SYSTEMS_DRAWTEXTURE_HPP_

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Scale.hpp"
#include "game/components/Size.hpp"
#include "game/components/Texture2D.hpp"
#include "raylib/textures/Texture2D.hpp"
#include "raylib/core/Window.hpp"

namespace game::systems
{
    struct DrawTexture : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            auto &textures = data.getStorage<game::components::Texture2D>();
            auto &poses = data.getStorage<game::components::Position>();
            auto &scales = data.getStorage<game::components::Scale>();
            auto &colors = data.getStorage<game::components::Color>();
            auto &rotations = data.getStorage<game::components::RotationAngle>();

            for (auto [texture, rotation, pos, scale, color] : ecs::join(textures, rotations, poses, scales, colors)) {
                texture.draw({pos.x / 100 * raylib::core::Window::getWidth(), pos.y / 100 * raylib::core::Window::getHeight()}, rotation.rotationAngle, scale.scale, color);
            }
        }
    };
} // namespace game::systems

#endif
