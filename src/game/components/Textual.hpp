/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Textual
*/

#ifndef GAME_GUI_COMPONENTS_TEXTUAL_HPP_
#define GAME_GUI_COMPONENTS_TEXTUAL_HPP_

#include "ecs/Component.hpp"

namespace game
{
    namespace gui
    {
        struct Textual : public ecs::Component {
            std::string text;

            Textual(std::string_view ptext) : text(ptext) {}
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_TEXTUAL_HPP_ */
