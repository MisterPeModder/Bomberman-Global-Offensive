/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Keybinds
*/

#ifndef GAME_SETTINGS_KEYBINDS_HPP_
#define GAME_SETTINGS_KEYBINDS_HPP_

#include <map>
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
            void setGamepadBinding(GamepadInput gamepadInput, GameAction action);

          private:
            std::map<raylib::core::Keyboard::Key, GameAction> _keyboardBindings;
            std::map<GamepadInput, GameAction> _gamepadBindings;
        };
    } // namespace settings
} // namespace game

#endif /* !GAME_SETTINGS_KEYBINDS_HPP_ */
