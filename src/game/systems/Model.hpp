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
                auto &models = data.getStorage<game::Model>();
                auto &poses = data.getStorage<game::Position>();
                auto &scales = data.getStorage<game::Scale>();
                auto &colors = data.getStorage<game::Color>();
                auto &sizes = data.getStorage<game::Size>();
                auto &rAxises = data.getStorage<game::RotationAxis>();
                auto &rAngles = data.getStorage<game::RotationAngle>();

                for (auto [model, pos, scale, color] : ecs::join(models, poses, scales, colors)) {
                    model.draw(pos, scale.scale, color);
                }
                for (auto [model, pos, rAxis, rAngle, size, color] :
                    ecs::join(models, poses, rAxises, rAngles, sizes, colors)) {
                    model.draw(pos, rAxis, rAngle.rotationAngle, size, color);
                }
            }
        };
    } // namespace systems
} // namespace game
