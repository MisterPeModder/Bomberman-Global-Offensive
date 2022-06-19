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
#include "game/components/Animation.hpp"
#include "game/components/GameEnded.hpp"
#include "game/components/Living.hpp"
#include "game/components/Player.hpp"
#include "game/components/Sound.hpp"
#include "game/scenes/MainMenuScene.hpp"

namespace game::systems
{
    /// CheckGameEnd system
    struct CheckGameEnd : public ecs::System {
        /// Return to main menu when only one player left
        void run(ecs::SystemData data) override final
        {
            auto &timer = data.getResource<ecs::Timer>();

            if (data.getStorage<game::components::Player>().size() <= 1) {
                for (auto [gameEnded] : ecs::join(data.getStorage<game::components::GameEnded>())) {
                    if (gameEnded.endTime + 5 <= timer.elapsed()) {
                        data.getResource<game::resources::EngineResource>().engine->setScene<game::MainMenuScene>();
                    }
                    if (!gameEnded.gameEnded) {
                        for (auto [living, entity] :
                            ecs::join(data.getStorage<game::components::Living>(), data.getResource<ecs::Entities>())) {
                            auto &randDevice = data.getResource<game::resources::RandomDevice>();
                            unsigned int randVal = randDevice.randInt(
                                static_cast<unsigned int>(game::components::Player::Animations::Dance_1),
                                static_cast<unsigned int>(game::components::Player::Animations::Dance_4));
                            auto &anim = data.getStorage<game::components::Animation>()[entity.getId()];
                            gameEnded.gameEnded = true;
                            gameEnded.endTime = timer.elapsed();
                            anim.chooseAnimation(randVal);
                            game::components::Sound::playSound(data, "victory");
                        }
                    }
                }
            }
        }
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_CHANGECUBE_HPP_ */
