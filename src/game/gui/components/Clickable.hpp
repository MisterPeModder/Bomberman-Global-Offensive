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
        struct Clickable final : public IWidgetComponent {
            enum class State { Default, Pressed };

            using OnClick = std::function<void(ecs::Entity)>;
            using OnStateChanged = std::function<void(ecs::Entity, State)>;

            State state;
            OnClick onClick;
            OnStateChanged onStateChanged;

            Clickable(OnClick ponClick) : state(State::Default), onClick(ponClick) {}
            Clickable(OnClick ponClick, OnStateChanged ponStateChanged)
                : state(State::Default), onClick(ponClick), onStateChanged(ponStateChanged)
            {
            }

            bool update(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event) override final;
        };
    } // namespace gui
} // namespace game

#endif /* !GAME_GUI_COMPONENTS_CLICKABLE_HPP_ */
