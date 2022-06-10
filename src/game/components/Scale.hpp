#ifndef GAME_COMPONENTS_SCALE_HPP_
#define GAME_COMPONENTS_SCALE_HPP_

#include "ecs/Component.hpp"

namespace game::components
{
    struct Scale : public ecs::Component {
        float scale;

        Scale(float pscale) : scale(pscale) {}
        Scale(int pscale) : scale(static_cast<float>(pscale)) {}
    };
} // namespace game::components

#endif
