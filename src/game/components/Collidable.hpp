/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Collidable
*/

#ifndef GAME_COMPONENTS_COLLIDABLE_HPP_
#define GAME_COMPONENTS_COLLIDABLE_HPP_

#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"

namespace game::components
{
    /// Collidable marker.
    /// @note Entities without a velocity components are considered statics and will not be moved when performing
    /// collision resolution.
    struct Collidable : public ecs::Component {
        //
    };

    /// Wall marker.
    struct Wall : public ecs::Component {
        //
    };
} // namespace game::components

SET_COMPONENT_STORAGE(game::components::Collidable, ecs::MarkerStorage);
SET_COMPONENT_STORAGE(game::components::Wall, ecs::MarkerStorage);

#endif /* !GAME_COMPONENTS_COLLIDABLE_HPP_ */
