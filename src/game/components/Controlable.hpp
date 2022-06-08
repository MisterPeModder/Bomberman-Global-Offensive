/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Controlable
*/

#ifndef GAME_COMPONENTS_CONTROLABLE_HPP_
#define GAME_COMPONENTS_CONTROLABLE_HPP_

#include "User.hpp"
#include "ecs/Component.hpp"

namespace game
{
    /// Controlable entity, may be a widget or a player
    struct Controlable : public ecs::Component {
        /// Id of the user controlling the widget
        User::UserId userId;

        Controlable(User::UserId id) : userId(id) {}
    };
} // namespace game

#endif /* !GAME_COMPONENTS_CONTROLABLE_HPP_ */
