#ifndef GAME_SYSTEMS_MODEL_HPP_
#define GAME_SYSTEMS_MODEL_HPP_

#include "ecs/System.hpp"
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
        struct DrawModel : public ecs::System {
            void run(ecs::SystemData data) override final
            {
                for (auto [model, pos, scale, color] :
                    ecs::join(data.getStorage<game::Model>(), data.getStorage<game::Position>(),
                        data.getStorage<game::Scale>(), data.getStorage<game::Color>())) {
                    model.draw(pos, scale.scale, color);
                }
            }
        };

        struct DrawRotatedModel : public ecs::System {
            void run(ecs::SystemData data) override final
            {
                for (auto [model, pos, rAxis, rAngle, size, color] :
                    ecs::join(data.getStorage<game::Model>(), data.getStorage<game::Position>(),
                        data.getStorage<game::RotationAxis>(), data.getStorage<game::RotationAngle>(),
                        data.getStorage<game::Size>(), data.getStorage<game::Color>())) {
                    model.draw(pos, rAxis, rAngle.rotationAngle, size, color);
                }
            }
        };
    } // namespace systems
} // namespace game

#endif
