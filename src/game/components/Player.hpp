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
        static constexpr float DefaultSpeed = 4.f;
        static bool handleActionEvent(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event);

      private:
        static void move(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event);
        static void placeBomb(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event);
    };
} // namespace game::components

SET_COMPONENT_STORAGE(game::components::Player, ecs::MarkerStorage);

#endif /* !GAME_COMPONENTS_PLAYER_HPP_ */
