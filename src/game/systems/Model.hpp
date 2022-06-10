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
                auto &model = data.getStorage<game::Model>();
                auto &pos = data.getStorage<game::Position>();
                auto &scale = data.getStorage<game::Scale>();
                auto &color = data.getStorage<game::Color>();
                auto &size = data.getStorage<game::Size>();
                auto &rAxis = data.getStorage<game::RotationAxis>();
                auto &rAngle = data.getStorage<game::RotationAngle>();

                for (auto [model1, pos1, scale1, color1] : ecs::join(model, pos, scale, color)) {
                    model1.draw(pos1, scale1.scale, color1);
                }
                for (auto [model1, pos1, rAxis1, rAngle1, size1, color1] :
                    ecs::join(model, pos, rAxis, rAngle, size, color)) {
                    model1.draw(pos1, rAxis1, rAngle1.rotationAngle, size1, color1);
                }
            }
        };
    } // namespace systems
} // namespace game
