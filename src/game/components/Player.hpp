/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Player
*/

#ifndef GAME_COMPONENTS_LIVING_HPP_
#define GAME_COMPONENTS_LIVING_HPP_

#include "ecs/Component.hpp"
#include "game/User.hpp"

namespace game
{
    struct Player : public ecs::Component {
        User::UserId playerId;

        Player(User::UserId pplayerId = User::UserId::User1) : playerId(pplayerId) {}
    };
} // namespace game

#endif /* !GAME_COMPONENTS_LIVING_HPP_ */
