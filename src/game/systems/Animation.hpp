/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** Animation
*/

#ifndef GAME_SYSTEMS_ANIMATION_HPP_
#define GAME_SYSTEMS_ANIMATION_HPP_

#include <iostream>
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

namespace game
{
    namespace systems
    {
        struct RunAnimation : public ecs::System {
            void run(ecs::SystemData data) override final
            {
                auto models = ecs::maybe(data.getStorage<game::components::Model>());
                auto modelRefs = ecs::maybe(data.getStorage<game::components::ModelReference>());

                for (auto [model, modelRef, animation] :
                    ecs::join(models, modelRefs, data.getStorage<game::components::Animation>())) {
                    auto obj = (model) ? model : ((modelRef) ? &modelRef->object : nullptr);

                    if (!obj)
                        continue;
                    animation.updateModel(*obj);
                }
            }
        };
    } // namespace systems
} // namespace game

#endif
