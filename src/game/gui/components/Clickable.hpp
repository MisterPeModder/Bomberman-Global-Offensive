/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Clickable
*/

#ifndef GAME_GUI_COMPONENTS_CLICKABLE_HPP_
#define GAME_GUI_COMPONENTS_CLICKABLE_HPP_

#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"

namespace game
{
    namespace gui
    {
        struct Clickable : public ecs::Component {
            enum class State { Default, Hovered, Pressed };
            State state;

            Clickable() : state(State::Default) {}
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_CLICKABLE_HPP_ */
