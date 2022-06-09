/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** InputManager
*/

#ifndef GAME_SYSTEMS_INPUTMANAGER_HPP_
#define GAME_SYSTEMS_INPUTMANAGER_HPP_

#include "ecs/System.hpp"
#include "game/Users.hpp"

namespace game
{
    /// System managing all the users inputs.
    struct InputManager : public ecs::System {
        /// Retreive all the users @ref Users::ActionEvent and send them to the controlable entities matching the
        /// UserId.
        ///
        /// @note Widgets will receive the events only if they are selected.
        ///
        /// @param data view on the world.
        void run(ecs::SystemData data) override final;

      private:
        void handleEvent(const Users::ActionEvent &event, ecs::SystemData data);
    };
} // namespace game

#endif /* !GAME_SYSTEMS_INPUTMANAGER_HPP_ */
