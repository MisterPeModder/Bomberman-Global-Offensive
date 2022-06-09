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
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "game/Users.hpp"

namespace game
{
    namespace gui
    {
        struct Widget : public ecs::Component {
            using WidgetTag = size_t;
            static constexpr WidgetTag NullTag = -1;
            WidgetTag tag;

            WidgetTag left;
            WidgetTag right;
            WidgetTag up;
            WidgetTag down;
            bool selected;

            Widget(WidgetTag ptag, WidgetTag pleft = NullTag, WidgetTag pright = NullTag, WidgetTag pup = NullTag,
                WidgetTag pdown = NullTag, bool pselected = false)
                : tag(ptag), left(pleft), right(pright), up(pup), down(pdown), selected(pselected)
            {
            }

            bool update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event);

          private:
            template <typename T>
            static bool tryUpdate(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event)
            {
                try {
                    auto &storage = data.getStorage<T>();

                    if (!storage.contains(self.getId()))
                        return false;
                    return storage[self.getId()].update(self, data, event);
                } catch (std::logic_error &) {
                    /// No storage for requested component
                    return false;
                }
            }

            bool updateSelection(ecs::SystemData data, const Users::ActionEvent &event);
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_WIDGET_HPP_ */
