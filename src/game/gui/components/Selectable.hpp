/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Selectable
*/

#ifndef GAME_GUI_SELECTABLE_HPP_
#define GAME_GUI_SELECTABLE_HPP_

#include "ecs/Component.hpp"

namespace game
{
    namespace gui
    {
        struct Selectable : public ecs::Component {
            bool selected;

            Selectable(bool pselected = false) : selected(pselected) {}
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_SELECTABLE_HPP_ */
