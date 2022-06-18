/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** KeybindIntercepter
*/

#ifndef GAME_COMPONENTS_KEYBINDINTERCEPTER_HPP_
#define GAME_COMPONENTS_KEYBINDINTERCEPTER_HPP_

#include "ecs/Component.hpp"
#include "game/Users.hpp"

namespace game::components
{
    struct KeybindIntercepter : public ecs::Component {
        game::User::UserId user;
        GameAction action;
        bool keyboard;

        KeybindIntercepter(game::User::UserId pUserId, GameAction pAction, bool pKeyboard = true)
            : user(pUserId), action(pAction), keyboard(pKeyboard){};
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_KEYBINDINTERCEPTER_HPP_ */
