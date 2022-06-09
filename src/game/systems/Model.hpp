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
        struct ModelsDraw : public ecs::System {
            void run(ecs::SystemData data) override final
            {
                for (auto [model, pos, scale, color] :
                    ecs::join(data.getStorage<game::components::Model>(), data.getStorage<game::components::Position>(),
                        data.getStorage<game::components::Scale>(), data.getStorage<game::components::Color>())) {
                    model.draw(pos, scale.scale, color);
                }
            }
        };

        struct ModelsDrawEX : public ecs::System {
            void run(ecs::SystemData data) override final
            {
                for (auto [model, pos, rAxis, rAngle, size, color] :
                    ecs::join(data.getStorage<game::components::Model>(), data.getStorage<game::components::Position>(),
                        data.getStorage<game::components::RotationAxis>(),
                        data.getStorage<game::components::RotationAngle>(), data.getStorage<game::components::Size>(),
                        data.getStorage<game::components::Color>())) {
                    model.draw(pos, rAxis, rAngle.rotationAngle, size, color);
                }
            }
        };
    }
} // namespace game
