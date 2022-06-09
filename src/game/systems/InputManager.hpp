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
    struct InputManager : public ecs::System {
        void run(ecs::SystemData data) override final;

      private:
        void handleEvent(const Users::ActionEvent &event, ecs::SystemData data);
    };
} // namespace game

#endif /* !GAME_SYSTEMS_INPUTMANAGER_HPP_ */
