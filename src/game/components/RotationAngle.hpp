#ifndef GAME_COMPONENTS_ROTATIONANGLE_HPP_
#define GAME_COMPONENTS_ROTATIONANGLE_HPP_

#include "ecs/Component.hpp"

namespace game
{
    namespace components
    {
        struct RotationAngle : public ecs::Component {
            float rotationAngle;

            RotationAngle(float protationAngle) : rotationAngle(protationAngle) {}
        };
    } // namespace components
} // namespace game

#endif
