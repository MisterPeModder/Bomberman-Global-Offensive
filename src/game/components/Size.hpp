#ifndef GAME_COMPONENTS_SIZE_HPP_
#define GAME_COMPONENTS_SIZE_HPP_

#include "ecs/Component.hpp"

namespace game
{
    namespace components
    {
        struct Size : public ecs::Component {
            float size;

            Size(float psize) : size(psize) {}
        };
    } // namespace components
} // namespace game

#endif
