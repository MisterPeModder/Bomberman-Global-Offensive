/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Widget
*/

#include "Widget.hpp"

#include "Clickable.hpp"

#include "logger/Logger.hpp"

namespace game
{
    namespace gui
    {
        bool Widget::update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event)
        {
            if (tryUpdate<Clickable>(self, data, event))
                return true;
            return false;
        }
    } // namespace gui
} // namespace game