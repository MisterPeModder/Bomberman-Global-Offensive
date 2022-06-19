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
        ACTION,
        TOGGLE_CONSOLE,
        BACK,
        ACTIVATE_ITEM,
        DISCONNECT,
        COUNT,
    };

    /// Test if a specified action is a move action.
    ///
    /// @param action action to test.
    /// @return true if the action is a MOVE_* action.
    /// @return false if the action is an other action.
    constexpr bool isMoveAction(GameAction action)
    {
        return (action == GameAction::MOVE_LEFT || action == GameAction::MOVE_DOWN || action == GameAction::MOVE_RIGHT
            || action == GameAction::MOVE_UP);
    }
} // namespace game

#endif /* !GAME_GAMEACTION_HPP_ */
