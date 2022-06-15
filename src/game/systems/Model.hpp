/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Model
*/

#ifndef GAME_SYSTEMS_MODEL_HPP_
#define GAME_SYSTEMS_MODEL_HPP_

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Scale.hpp"
#include "game/components/Size.hpp"
#include "raylib/model/Model.hpp"

namespace game::systems
{
    struct DrawModel : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            auto &models = data.getStorage<game::components::Model>();
            auto &poses = data.getStorage<game::components::Position>();
            auto &scales = data.getStorage<game::components::Scale>();
            auto &colors = data.getStorage<game::components::Color>();
            auto &sizes = data.getStorage<game::components::Size>();
            auto &rAxises = data.getStorage<game::components::RotationAxis>();
            auto &rAngles = data.getStorage<game::components::RotationAngle>();

            for (auto [model, pos, rAxis, rAngle, size, color] :
                ecs::join(models, poses, rAxises, rAngles, sizes, colors)) {
                model.draw(pos, rAxis.rotationAxis, rAngle.rotationAngle, size, color);
            }
            for (auto [model, pos, scale, color] : ecs::join(models, poses, scales, colors)) {
                model.draw(pos, scale.scale, color);
            }
        }
    };
} // namespace game::systems

#endif
