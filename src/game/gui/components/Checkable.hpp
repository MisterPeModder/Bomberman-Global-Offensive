/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Checkable
*/

#ifndef GAME_GUI_COMPONENTS_CHECKABLE_HPP_
#define GAME_GUI_COMPONENTS_CHECKABLE_HPP_

#include <functional>
#include "IWidgetComponent.hpp"

namespace game
{
    namespace gui
    {
        /// Checkable component, used for checkbox widgets.
        struct Checkable final : public IWidgetComponent {
            /// Callback called when the checkbox is checked/unchecked.
            ///
            /// @param ecs::Entity entity @a owning the component.
            /// @param bool set to true if the component is checked.
            using OnStateChanged = std::function<void(ecs::Entity, bool)>;

            /// Callback called when the checkbox is checked/unchecked.
            OnStateChanged onStateChanged;
            /// Set to true if the component is checked.
            bool checked;

            /// Construct a new Checkable component
            ///
            /// @param ponStateChanged Callback called when the checkbox is checked/unchecked.
            /// @param startChecked set to true if the component must start checked.
            ///
            Checkable(OnStateChanged ponStateChanged, bool startChecked = false)
                : onStateChanged(ponStateChanged), checked(startChecked)
            {
            }

            /// @copydoc IWidgetComponent::update.
            bool update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event) override final;
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_CHECKABLE_HPP_ */
