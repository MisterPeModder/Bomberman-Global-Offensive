/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** KeybindIntercept
*/

#ifndef GAME_SYSTEMS_KEYBINDINTERCEPT_HPP_
#define GAME_SYSTEMS_KEYBINDINTERCEPT_HPP_

#include "ecs/System.hpp"
#include "game/Engine.hpp"
#include "game/Users.hpp"
#include "game/components/KeybindIntercepter.hpp"

#include "logger/Logger.hpp"

namespace game::systems
{
    struct KeybindIntercept : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            auto &entities = data.getResource<ecs::Entities>();
            auto &users = data.getResource<resources::EngineResource>().engine->getUsers();

            for (auto [intercepter, id] :
                ecs::join(data.getStorage<game::components::KeybindIntercepter>(), entities)) {
                if (intercepter.keyboard) {
                    raylib::core::Keyboard::Key key = raylib::core::Keyboard::getKeyPressed();

                    if (key != raylib::core::Keyboard::Key::NONE) {
                        Logger::logger.log(Logger::Severity::Information,
                            "Got user input " + std::to_string(static_cast<size_t>(key)));
                        users.updateActions(false);
                        entities.kill(id);
                    }
                } else {
                }
            }
        }
    };
} // namespace game::systems

#endif /* !KEYBINDINTERCEPT_HPP_ */
