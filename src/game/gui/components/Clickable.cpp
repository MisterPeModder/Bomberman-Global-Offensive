/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Clickable
*/

#include "Clickable.hpp"

namespace game
{
    namespace gui
    {
        bool Clickable::update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event)
        {
            (void)data;
            if (event.action != GameAction::ACTION)
                return false;
            State newState = state;

            if (event.value > 0.f)
                newState = State::Pressed;
            else
                newState = State::Default;
            if (newState != state) {
                state = newState;
                if (onStateChanged)
                    onStateChanged(self, state);
                if (newState == State::Default && onClick)
                    onClick(self);
            }
            return true;
        };
    } // namespace gui
} // namespace game
