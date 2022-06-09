/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Widget
*/

#include "Widget.hpp"
#include "ecs/join.hpp"

#include "Checkable.hpp"
#include "Clickable.hpp"

namespace game
{
    namespace gui
    {
        bool Widget::update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event)
        {
            if (tryUpdate<Clickable>(self, data, event))
                return true;
            if (tryUpdate<Checkable>(self, data, event))
                return true;

            return updateSelection(data, event);
        }

        bool Widget::updateSelection(ecs::SystemData data, const Users::ActionEvent &event)
        {
            if (event.value < 0.7f
                || ((event.action != GameAction::MOVE_LEFT || left == NullTag)
                    && (event.action != GameAction::MOVE_RIGHT || right == NullTag)
                    && (event.action != GameAction::MOVE_UP || up == NullTag)
                    && (event.action != GameAction::MOVE_DOWN || down == NullTag)))
                return false;
            WidgetId newSelected;

            switch (event.action) {
                case GameAction::MOVE_LEFT: newSelected = left; break;
                case GameAction::MOVE_RIGHT: newSelected = right; break;
                case GameAction::MOVE_UP: newSelected = up; break;
                case GameAction::MOVE_DOWN: newSelected = down; break;
            }

            /// If the new widget to select isn't found, the current widget keep the selection.
            for (auto [widget] : ecs::join(data.getStorage<Widget>())) {
                if (widget.tag == newSelected) {
                    selected = false;
                    widget.selected = true;
                    return true;
                }
            }
            return false;
        }
    } // namespace gui
} // namespace game
