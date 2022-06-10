/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Textual
*/

#ifndef GAME_GUI_COMPONENTS_TEXTUAL_HPP_
#define GAME_GUI_COMPONENTS_TEXTUAL_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Color.hpp"

namespace game
{
    /// Textual element.
    struct Textual : public ecs::Component {
        /// Text printed.
        std::string text;
        /// Size of the text.
        size_t fontSize;
        /// Color of the text.
        raylib::core::Color color;

        /// Construct a new Textual component.
        ///
        /// @param ptext text printed.
        /// @param pfontSize size of the text.
        /// @param pcolor color of the text.
        Textual(
            std::string_view ptext, size_t pfontSize = 20, raylib::core::Color pcolor = raylib::core::Color::LIGHT_GRAY)
            : text(ptext), fontSize(pfontSize), color(pcolor)
        {
        }
    };
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_TEXTUAL_HPP_ */
