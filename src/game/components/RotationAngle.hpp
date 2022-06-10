#ifndef GAME_COMPONENTS_ROTATIONANGLE_HPP_
#define GAME_COMPONENTS_ROTATIONANGLE_HPP_

#include "ecs/Component.hpp"

namespace game::components
{
    struct RotationAngle : public ecs::Component {
        float rotationAngle;

        RotationAngle(float protationAngle) : rotationAngle(protationAngle) {}
        RotationAngle(int protationAngle) : rotationAngle(static_cast<float>(protationAngle)) {}
    };
} // namespace game::components

#endif
