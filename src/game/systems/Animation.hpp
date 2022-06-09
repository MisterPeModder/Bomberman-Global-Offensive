#include <iostream>
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
        struct RunAnimation : public ecs::System {
            void run(ecs::SystemData data) override final
            {
                for (auto [model, animation] : ecs::join(
                         data.getStorage<game::components::Model>(), data.getStorage<game::components::Animation>())) {
                    animation.updateModel(model);
                }
            }
        };
    } // namespace systems
} // namespace game
