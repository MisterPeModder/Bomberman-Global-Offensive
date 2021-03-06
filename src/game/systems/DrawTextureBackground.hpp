/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** DrawTexture
*/

#ifndef GAME_SYSTEMS_DRAWTEXTUREBACKGROUND_HPP_
#define GAME_SYSTEMS_DRAWTEXTUREBACKGROUND_HPP_

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Background.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Scale.hpp"
#include "game/components/Size.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/textures/Texture2D.hpp"

namespace game::systems
{
    struct DrawTextureBackground : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            auto &textures = data.getStorage<game::components::Background>();
            auto &poses = data.getStorage<game::components::Position>();
            auto &scales = data.getStorage<game::components::Scale>();
            auto &colors = data.getStorage<game::components::Color>();
            auto &rotations = data.getStorage<game::components::RotationAngle>();

            for (auto [texture, rotation, pos, scale, color] : ecs::join(textures, rotations, poses, scales, colors)) {
                texture.draw(
                    {pos.x / 100 * raylib::core::Window::getWidth(), pos.y / 100 * raylib::core::Window::getHeight()},
                    rotation.rotationAngle, scale.scale * (static_cast<float>(raylib::core::Window::getWidth()) / 1000),
                    color);
            }
        }
    };
} // namespace game::systems

#endif
