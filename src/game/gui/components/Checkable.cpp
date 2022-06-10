/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Checkable
*/

#include "Checkable.hpp"

namespace game
{
    namespace gui
    {
        bool Checkable::update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event)
        {
            (void)data;
            if (event.action != GameAction::ACTION)
                return false;

            if (event.value == 0.f) {
                checked = !checked;
                if (onStateChanged)
                    onStateChanged(self, checked);
            }
            return true;
        };
    } // namespace gui
} // namespace game
