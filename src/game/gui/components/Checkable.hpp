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
        struct Checkable final : public IWidgetComponent {
            using OnStateChanged = std::function<void(ecs::Entity, bool)>;

            OnStateChanged onStateChanged;
            bool checked;

            Checkable(OnStateChanged ponStateChanged, bool startChecked = false)
                : onStateChanged(ponStateChanged), checked(startChecked)
            {
            }

            bool update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event) override final;
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_CHECKABLE_HPP_ */
