/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** PlaySoundOnce
*/

#ifndef GAME_SYSTEMS_PLAYSOUNDONCE_HPP_
#define GAME_SYSTEMS_PLAYSOUNDONCE_HPP_

#include <iostream>
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Sound.hpp"
#include "game/components/UseCheck.hpp"

namespace game
{
    namespace systems
    {
        struct PlaySoundOnce : public ecs::System {
            void run(ecs::SystemData data) override final
            {
                for (auto [sound, useCheck] : ecs::join(
                         data.getStorage<game::components::Sound>(), data.getStorage<game::components::UseCheck>())) {
                    if (!useCheck.used) {
                        std::cout << "play sound" << std::endl;
                        sound.setVolume(
                            data.getResource<resources::EngineResource>().engine->getSettings().getSfxVolume());
                        sound.play();
                        useCheck.used = true;
                    } else
                        std::cout << "not play sound" << std::endl;
                }
            }
        };
    } // namespace systems
} // namespace game

#endif
