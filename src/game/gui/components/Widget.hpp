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
#include "ecs/World.hpp"
#include "game/components/Controlable.hpp"

namespace game
{
    namespace gui
    {
        struct Widget : public ecs::Component {
            using WidgetTag = size_t;
            static constexpr WidgetTag NullTag = -1;
            WidgetTag tag;

            WidgetTag previous;
            WidgetTag next;
            bool selected;

            Widget(WidgetTag ptag, WidgetTag pprevious = NullTag, WidgetTag pnext = NullTag, bool pselected = false)
                : tag(ptag), previous(pprevious), next(pnext), selected(pselected)
            {
            }

            bool update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event);
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_WIDGET_HPP_ */
