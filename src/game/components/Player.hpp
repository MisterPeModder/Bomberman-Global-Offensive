/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Collidable
*/

#ifndef GAME_COMPONENTS_PLAYER_HPP_
#define GAME_COMPONENTS_PLAYER_HPP_

#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "game/Users.hpp"

namespace game::components
{
    /// Player marker.
    struct Player : public ecs::Component {
        /// Default speed of the player (in cells per seconds)
        static constexpr float DefaultSpeed = 4.f;

        /// Callback of the @ref Controlable component of the players.
        ///
        /// @param self player entity
        /// @param data world data
        /// @param event action event
        /// @return true If the action was consumed.
        /// @return false If the action wasn't consumed.
        static bool handleActionEvent(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event);

      private:
        /// Change the velocity of the player from its action values.
        ///
        /// @param self player entity
        /// @param data world data
        /// @param event action event
        static void move(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event);

        /// Place a bomb at the player position.
        ///
        /// @param self player entity
        /// @param data world data
        /// @return true If the action was consumed.
        /// @return false If the action wasn't consumed.
        static void placeBomb(ecs::Entity self, ecs::SystemData data);
    };
} // namespace game::components

SET_COMPONENT_STORAGE(game::components::Player, ecs::MarkerStorage);

#endif /* !GAME_COMPONENTS_PLAYER_HPP_ */
