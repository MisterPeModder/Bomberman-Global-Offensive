/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Controlable
*/

#ifndef GAME_COMPONENTS_CONTROLABLE_HPP_
#define GAME_COMPONENTS_CONTROLABLE_HPP_

#include <functional>
#include "ecs/Component.hpp"
#include "ecs/System.hpp"
#include "game/Users.hpp"

namespace game
{
    /// Controlable entity, may be a widget or a player
    struct Controlable : public ecs::Component {
        /// Callback called when an action with the matching @c userId is detected.
        ///
        /// @param ecs::Entity entity @a owning the controlable component.
        /// @param ecs::SystemData view on the world.
        /// @param const Users::ActionEvent& informations about the action detected.
        /// @retval true if the action was consumed.
        /// @retval false otherwise.
        using ActionCallback = std::function<bool(ecs::Entity, ecs::SystemData, const Users::ActionEvent &)>;

        /// Id of the user controlling the widget.
        User::UserId userId;
        /// Callback called when an action is detected for the user @c userId.
        ActionCallback callback;

        /// Construct a new Controlable component.
        ///
        /// @param id id of the user controling the component.
        Controlable(User::UserId id) : userId(id) {}

        /// Construct a new Controlable component.
        ///
        /// @param id id of the user controling the component.
        /// @param pcallback callback called when an action of the listened user is detected.
        Controlable(User::UserId id, ActionCallback pcallback) : userId(id), callback(pcallback) {}
    };
} // namespace game

#endif /* !GAME_COMPONENTS_CONTROLABLE_HPP_ */
