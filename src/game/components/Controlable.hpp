/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Controlable
*/

#ifndef GAME_COMPONENTS_CONTROLABLE_HPP_
#define GAME_COMPONENTS_CONTROLABLE_HPP_

#include <functional>
#include "ecs/Component.hpp"
#include "game/Users.hpp"

namespace game
{
    /// Controlable entity, may be a widget or a player
    struct Controlable : public ecs::Component {
        using Callback = std::function<bool(const Users::ActionEvent &)>;

        /// Id of the user controlling the widget
        User::UserId userId;
        Callback callback;

        Controlable(User::UserId id) : userId(id) {}
        Controlable(User::UserId id, Callback pcallback) : userId(id), callback(pcallback) {}
    };
} // namespace game

#endif /* !GAME_COMPONENTS_CONTROLABLE_HPP_ */
