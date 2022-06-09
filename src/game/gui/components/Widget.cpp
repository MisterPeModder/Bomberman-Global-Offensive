/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Widget
*/

#include "Widget.hpp"

#include "logger/Logger.hpp"

namespace game
{
    namespace gui
    {
        bool Widget::update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event)
        {
            (void)self;
            (void)data;
            (void)event;

            Logger::logger.log(Logger::Severity::Debug, "Update widget");

            return false;
        }
    } // namespace gui
} // namespace game