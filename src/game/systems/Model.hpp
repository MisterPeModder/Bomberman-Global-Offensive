/*
** EPITECH PROJECT, 2022
** BMGO
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
            auto models = ecs::maybe(data.getStorage<game::components::Model>());
            auto modelRefs = ecs::maybe(data.getStorage<game::components::ModelReference>());
            auto &poses = data.getStorage<game::components::Position>();
            auto &colors = data.getStorage<game::components::Color>();
            auto scales = ecs::maybe(data.getStorage<game::components::Scale>());
            auto sizes = ecs::maybe(data.getStorage<game::components::Size>());
            auto rAxises = ecs::maybe(data.getStorage<game::components::RotationAxis>());
            auto rAngles = ecs::maybe(data.getStorage<game::components::RotationAngle>());

            for (auto [model, modelRef, pos, color, scale, size, rAxis, rAngle] :
                ecs::join(models, modelRefs, poses, colors, scales, sizes, rAxises, rAngles)) {
                auto obj = (model) ? model : ((modelRef) ? &modelRef->object : nullptr);

                if (!obj)
                    continue;
                /// Prior to extended draw.
                if (size && rAxis && rAngle)
                    obj->draw(pos, *rAxis, rAngle->rotationAngle, *size, color);
                else if (scale)
                    obj->draw(pos, scale->scale, color);
            }
        }
    };
} // namespace game::systems

#endif
