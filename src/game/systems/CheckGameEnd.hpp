/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** ChangeCube
*/

#ifndef GAME_SYSTEMS_CHANGECUBE_HPP_
#define GAME_SYSTEMS_CHANGECUBE_HPP_

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "game/Engine.hpp"
#include "game/components/Player.hpp"
#include "game/scenes/MainMenuScene.hpp"

namespace game::systems
{
    /// CheckGameEnd system
    struct CheckGameEnd : public ecs::System {
        /// Return to main menu when only one player left
        void run(ecs::SystemData data) override final
        {
            if (data.getStorage<game::components::Player>().size() <= 1)
                data.getResource<game::resources::EngineResource>().engine->setScene<game::MainMenuScene>();
        }
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_CHANGECUBE_HPP_ */
