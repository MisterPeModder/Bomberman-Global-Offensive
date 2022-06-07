/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Keybinds
*/

#ifndef GAME_SETTINGS_KEYBINDS_HPP_
#define GAME_SETTINGS_KEYBINDS_HPP_

#include <map>
#include <ostream>
#include "GamepadInput.hpp"
#include "game/GameAction.hpp"
#include "raylib/core/Keyboard.hpp"

namespace game
{
    namespace settings
    {
        /// Bindings of keyboards/gamepad inputs to game actions.
        class Keybinds {
          public:
            /// Construct a default keybinds set.
            /// @note Will call @ref loadDefaults().
            Keybinds();

            /// Construct a copy of a Keybinds object
            ///
            /// @param other keybinds to copy.
            Keybinds(const Keybinds &other) = default;

            /// Destroy a keybinds object.
            ~Keybinds() = default;

            /// Copy a Keybinds object.
            ///
            /// @param other keybinds to copy.
            /// @return Keybinds& @b this.
            Keybinds &operator=(const Keybinds &other) = default;

            /// Load the game default keybinds.
            /// @todo Add some documentation for the default keybinds and link it here.
            void loadDefaults();

            /// Delete all the bindings.
            void clear();

            /// Bind a keyboard key to a game action.
            /// @note Multiple key can be bound to the same action.
            /// @note Binding a key that was previously bind to an action will override the bind.
            ///
            /// @param key key.
            /// @param action game action.
            void setKeyboardBinding(raylib::core::Keyboard::Key key, GameAction action);

            /// Unbind a key from its game action.
            /// @note Does nothing if the key is already unbound.
            ///
            /// @param key key to unbind.
            void unbindKey(raylib::core::Keyboard::Key key);

            /// Bind a gamepad input to a game action.
            /// @note Multiple inputs can be bound to the same action.
            /// @note Binding a gamepad input that was previously bind to an action will override the bind.
            ///
            /// @param gamepadInput input.
            /// @param action game action.
            void setGamepadBinding(const GamepadInput &gamepadInput, GameAction action);

            /// Unbind a gamepad input from its game action.
            /// @note Does nothing if the gamepad input is already unbound.
            ///
            /// @param gamepadInput gamepad input to unbind.
            void unbindGamepadInput(const GamepadInput &gamepadInput);

            /// Get the map of the keyboard bindings.
            ///
            /// @return const std::map<raylib::core::Keyboard::Key, GameAction>& bindings map.
            ///
            const std::map<raylib::core::Keyboard::Key, GameAction> &getKeyboardBindings() const;

            /// Get the map of the gamepad bindings.
            ///
            /// @return const std::map<GamepadInput, GameAction>& bindings map.
            ///
            const std::map<GamepadInput, GameAction> &getGamepadBindings() const;

            /// Output the bindings in the @c stream.
            /// @note This is used to save bindings in files between sessions.
            ///
            /// @param stream output stream.
            /// @return const Keybinds& @b this.
            ///
            const Keybinds &operator>>(std::ostream &stream) const;

          private:
            std::map<raylib::core::Keyboard::Key, GameAction> _keyboardBindings;
            std::map<GamepadInput, GameAction> _gamepadBindings;
        };
    } // namespace settings
} // namespace game

/// Output stream operator overload.
/// @note This function is used for the keybinds save in the file.
///
/// @param stream output stream.
/// @param keybinds keybinds to export.
/// @return std::ostream& output stream.
std::ostream &operator<<(std::ostream &stream, const game::settings::Keybinds keybinds);

#endif /* !GAME_SETTINGS_KEYBINDS_HPP_ */
