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
    struct Textual : public ecs::Component {
        std::string text;
        size_t fontSize;
        raylib::core::Color color;

        Textual(
            std::string_view ptext, size_t pfontSize = 20, raylib::core::Color pcolor = raylib::core::Color::LIGHT_GRAY)
            : text(ptext), fontSize(pfontSize), color(pcolor)
        {
        }
    };
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_TEXTUAL_HPP_ */
