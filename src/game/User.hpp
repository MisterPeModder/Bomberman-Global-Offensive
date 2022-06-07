/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** User
*/

#ifndef GAME_USER_HPP_
#define GAME_USER_HPP_

#include <array>
#include <queue>
#include "settings/Profile.hpp"

namespace game
{
    /// User with specific profile/gamepad attributed.
    class User {
      public:
        /// Id of a user.
        enum class UserId {
            User1,     /// First user
            User2,     /// Second user
            User3,     /// Third user
            User4,     /// Fourth user
            UserCount, /// Number of simultaneaous users possible, Invalid for all functions taking a UserId
        };

        /// Create a new User.
        ///
        /// @param id id of the user.
        /// @param gamepadId id of the gamepad. -1 for keyboard inputs.
        User(UserId id = UserId::User1, int gamepadId = -1);

        /// Destroy the user.
        ~User() = default;

        /// Set the user in keyboard mode.
        void setKeyboard();

        /// Test if the user is in keyboard mode.
        ///
        /// @retval true if the user is in keyboard mode.
        /// @retval false if the user is in gamepad mode.
        bool isKeyboard() const;

        /// Set the Gamepad Id of the user.
        /// @note Setting the gamepad Id of a user will set it in gamepad mode.
        /// @warning Setting a negative gamepad Id will set the user in keyboard mode.
        ///
        /// @param id id of the gamepad.
        void setGamepadId(int id);

        /// Get the Gamepad Id of the user.
        ///
        /// @return int gamepad id.
        int getGamepadId() const;

        /// Set the user id.
        void setId(UserId id);

        /// Get the user id.
        ///
        /// @return UserId user id.
        UserId getId() const;

        /// Set the user available (connected)
        ///
        /// @param available wheter or not the user is available.
        /// @todo Detect new gamepad availables.
        void setAvailable(bool available);

        /// Test if the user is available.
        ///
        /// @retval true if the user is available.
        /// @retval false if the user isn't available.
        bool isAvailable() const;

        /// Get the Action value of a @ref GameAction.
        ///
        /// @param action action to check.
        /// @param update wheter or not the action value must be updated from the keyboard/gamepad status or not. (If
        /// false, it will use the last values).
        /// @return float value between [0, 1]. See @ref Users::ActionEvent::value
        float getActionValue(GameAction action, bool update = false);

        /// Get the last changed action of the user (action started/ended).
        /// @note The action value can be retreived using @ref getActionValue().
        ///
        /// @return action changed since last queue check.
        GameAction getChangedAction();

      private:
        void fillActions();

        int _gamepadId;
        bool _available;
        settings::Profile _profile;

        std::queue<GameAction> _changedActions;
        std::array<float, static_cast<size_t>(GameAction::BACK)> _lastActions;
    };
} // namespace game

#endif /* !GAME_USER_HPP_ */
