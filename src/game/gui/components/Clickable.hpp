/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Clickable
*/

#ifndef GAME_GUI_COMPONENTS_CLICKABLE_HPP_
#define GAME_GUI_COMPONENTS_CLICKABLE_HPP_

#include <functional>
#include "IWidgetComponent.hpp"

namespace game
{
    namespace gui
    {
        /// Clickable component.
        struct Clickable final : public IWidgetComponent {
            /// State of the component.
            enum class State {
                Default, /// Default state
                Pressed, /// The component is pressed and the OnClick event will be executed when it will be released
            };

            /// Callback called when the component state change from pressed to default.
            ///
            /// @param ecs::Entityentity @a owning the component.
            using OnClick = std::function<void(ecs::Entity)>;

            /// Callback called when the component state change.
            ///
            /// @param ecs::Entity entity @a owning the component.
            /// @param State current state.
            using OnStateChanged = std::function<void(ecs::Entity, State)>;

            /// Current state.
            State state;
            /// On click callback.
            OnClick onClick;
            /// On State changed callback
            OnStateChanged onStateChanged;

            /// Construct a new Clickable component.
            ///
            /// @param ponClick on click callback.
            Clickable(OnClick ponClick) : state(State::Default), onClick(ponClick) {}

            /// Construct a new Clickable component
            ///
            /// @param ponClick on click callback.
            /// @param ponStateChanged on state changed callback.
            Clickable(OnClick ponClick, OnStateChanged ponStateChanged)
                : state(State::Default), onClick(ponClick), onStateChanged(ponStateChanged)
            {
            }

            /// @copydoc IWidgetComponent::update.
            bool update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event) override final;
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_CLICKABLE_HPP_ */
