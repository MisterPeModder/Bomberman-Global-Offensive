/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Widget
*/

#ifndef GAME_GUI_COMPONENTS_WIDGET_HPP_
#define GAME_GUI_COMPONENTS_WIDGET_HPP_

#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"

namespace game
{
    namespace gui
    {
        struct Widget : public ecs::Component {
            ecs::Entity::Index previous;
            bool selected;

            Widget(ecs::Entity::Index previousWidget) : previous(previousWidget) { selected = false; }
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_WIDGET_HPP_ */
