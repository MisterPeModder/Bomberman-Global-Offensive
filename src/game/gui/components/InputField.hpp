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
        static constexpr double BACKSPACE_DELAY = 0.0625;

        std::string contents;
        bool selected;
        double backspaceCooldown;

        InputField(std::string &&initialContents = std::string(), bool pSelected = false)
            : contents(initialContents), selected(pSelected), backspaceCooldown(BACKSPACE_DELAY){};
    };
} // namespace game::gui

#endif // !defined(GAME_GUI_COMPONENTS_INPUT_FIELD_HPP_)
