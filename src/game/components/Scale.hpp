#ifndef GAME_COMPONENTS_SCALE_HPP_
#define GAME_COMPONENTS_SCALE_HPP_

#include "ecs/Component.hpp"

namespace game::components
{
    struct Scale : public ecs::Component {
        float scale;

        Scale(float pScale) : scale(pScale) {}
    };
} // namespace game::components

#endif
