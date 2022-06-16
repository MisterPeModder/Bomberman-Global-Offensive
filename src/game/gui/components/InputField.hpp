/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** InputField
*/

#ifndef GAME_GUI_COMPONENTS_INPUT_FIELD_HPP_
#define GAME_GUI_COMPONENTS_INPUT_FIELD_HPP_

#include "ecs/Component.hpp"

namespace game::gui
{
    /// Keyboard-only input field
    struct InputField : public ecs::Component {
        /// The minimum number of seconds between each character delete when the backspace key is pressed.
        static constexpr double BACKSPACE_REPEAT_DELAY = 0.025;
        /// The amount of seconds before the backspace key event starts repeating.
        static constexpr double BACKSPACE_REPEAT_THRESHOLD = 0.5;

        std::string contents;
        bool selected;
        double backspaceCooldown;
        double timeSinceBackspace;

        InputField(std::string &&initialContents = std::string(), bool pSelected = false)
            : contents(initialContents), selected(pSelected), backspaceCooldown(BACKSPACE_REPEAT_DELAY),
              timeSinceBackspace(0.0){};
    };
} // namespace game::gui

#endif // !defined(GAME_GUI_COMPONENTS_INPUT_FIELD_HPP_)
