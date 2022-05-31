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
        class Keybinds {
          public:
            Keybinds();
            ~Keybinds() = default;

            void loadDefaults();

            void setKeyboardBinding(raylib::core::Keyboard::Key key, GameAction action);
            void unbindKey(raylib::core::Keyboard::Key key);
            void setGamepadBinding(const GamepadInput &gamepadInput, GameAction action);
            void unbindGamepadInput(const GamepadInput &gamepadInput);

            const std::map<raylib::core::Keyboard::Key, GameAction> &getKeyboardBindings() const;
            const std::map<GamepadInput, GameAction> &getGamepadBindings() const;

            const Keybinds &operator>>(std::ostream &stream) const;

          private:
            std::map<raylib::core::Keyboard::Key, GameAction> _keyboardBindings;
            std::map<GamepadInput, GameAction> _gamepadBindings;
        };
    } // namespace settings
} // namespace game

std::ostream &operator<<(std::ostream &stream, const game::settings::Keybinds keybinds);

#endif /* !GAME_SETTINGS_KEYBINDS_HPP_ */
