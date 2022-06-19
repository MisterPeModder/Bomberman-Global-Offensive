/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** KeybindIntercepter
*/

#ifndef GAME_COMPONENTS_KEYBINDINTERCEPTER_HPP_
#define GAME_COMPONENTS_KEYBINDINTERCEPTER_HPP_

#include <functional>
#include "ecs/Component.hpp"
#include "game/Users.hpp"

namespace game::components
{
    struct KeybindIntercepter : public ecs::Component {
        using Callback = std::function<void(void)>;
        game::User::UserId user;
        GameAction action;
        Callback callback;
        bool keyboard;

        KeybindIntercepter(game::User::UserId pUserId, GameAction pAction, Callback pCallback, bool pKeyboard = true)
            : user(pUserId), action(pAction), callback(pCallback), keyboard(pKeyboard){};
        KeybindIntercepter(game::User::UserId pUserId, GameAction pAction, bool pKeyboard = true)
            : user(pUserId), action(pAction), keyboard(pKeyboard){};
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_KEYBINDINTERCEPTER_HPP_ */
