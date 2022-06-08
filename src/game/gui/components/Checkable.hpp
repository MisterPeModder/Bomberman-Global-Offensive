/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Checkable
*/

#ifndef GAME_GUI_COMPONENTS_CLICKABLE_HPP_
#define GAME_GUI_COMPONENTS_CLICKABLE_HPP_

#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"

namespace game
{
    namespace gui
    {
        struct Checkable : public ecs::Component {
            bool checked;

            Checkable(bool startChecked = false) : checked(startChecked) {}
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_CLICKABLE_HPP_ */
