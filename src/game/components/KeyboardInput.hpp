/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** KeyboardInput
*/

#ifndef GAME_COMPONENTS_INPUT_FIELD_HPP_
#define GAME_COMPONENTS_INPUT_FIELD_HPP_

#include "ecs/Component.hpp"

#include "raylib/core/Color.hpp"

namespace game
{
    /// Keyboard-only input field
    struct KeyboardInput : public ecs::Component {
        /// The minimum number of seconds between each character delete when the backspace key is pressed.
        static constexpr double BACKSPACE_REPEAT_DELAY = 0.025;
        /// The amount of seconds before the backspace key event starts repeating.
        static constexpr double BACKSPACE_REPEAT_THRESHOLD = 0.5;

        std::string contents;
        bool focused;
        double backspaceCooldown;
        double timeSinceBackspace;

        KeyboardInput(std::string &&initialContents = std::string(), bool pFocused = false)
            : contents(initialContents), focused(pFocused), backspaceCooldown(BACKSPACE_REPEAT_DELAY),
              timeSinceBackspace(0.0){};
    };
} // namespace game

#endif // !defined(GAME_COMPONENTS_INPUT_FIELD_HPP_)
