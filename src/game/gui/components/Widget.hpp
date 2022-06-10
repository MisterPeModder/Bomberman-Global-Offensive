/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Widget
*/

#ifndef GAME_GUI_COMPONENTS_WIDGET_HPP_
#define GAME_GUI_COMPONENTS_WIDGET_HPP_

#include "IWidgetComponent.hpp"
#include "ecs/Storage.hpp"

namespace game
{
    namespace gui
    {
        /// Widget component.
        struct Widget final : public IWidgetComponent {
            /// Widget Id, mandatory to link widgets together.
            using WidgetId = size_t;
            /// Id meaning none.
            static constexpr WidgetId NullTag = -1;
            /// Id of the widget
            WidgetId id;

            /// Id of the left widget
            WidgetId left;
            /// Id of the right widget
            WidgetId right;
            /// Id of the top widget
            WidgetId up;
            /// Id of the bottom widget
            WidgetId down;
            /// If the widget is the one selected
            bool selected;

            /// Construct a new Widget component
            /// @warning Only one widget should be selected, multiple widgets selected may lead to undefined behavior.
            ///
            /// @param pid id of the widget.
            /// @param pleft id of the left widget.
            /// @param pright id of the right widget.
            /// @param pup id of the top widget.
            /// @param pdown id of the bottom widget.
            /// @param pselected if the widget is selected.
            ///
            Widget(WidgetId pid, WidgetId pleft = NullTag, WidgetId pright = NullTag, WidgetId pup = NullTag,
                WidgetId pdown = NullTag, bool pselected = false)
                : id(pid), left(pleft), right(pright), up(pup), down(pdown), selected(pselected)
            {
            }

            /// @copydoc IWidgetComponent::update
            bool update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event) override final;

          private:
            /// Try to update a widget as a given component.
            ///
            /// @tparam T widget component to test.
            /// @param self entity @a owning the component.
            /// @param data view on the world.
            /// @param event action event.
            /// @return true if the component consumed the event
            /// @return false if the event wasn't used.
            ///
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

            /// Update the selected widget.
            ///
            /// @param data view on the world.
            /// @param event action event.
            /// @return true if the selection changed
            /// @return false if the selected widget hasn't changed.
            ///
            bool updateSelection(ecs::SystemData data, const Users::ActionEvent &event);
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_WIDGET_HPP_ */
