/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** GameAction
*/

#ifndef GAME_GAMEACTION_HPP_
#define GAME_GAMEACTION_HPP_

namespace game
{
    enum class GameAction {
        NONE,
        MOVE_LEFT,
        MOVE_UP,
        MOVE_RIGHT,
        MOVE_DOWN,
        PLACE_BOMB,
        PAUSE,
    };
}

#endif /* !GAME_GAMEACTION_HPP_ */
