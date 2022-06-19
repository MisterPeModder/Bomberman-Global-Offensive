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
                        Logger::logger.log(Logger::Severity::Information, [&](auto &out) {
                            out << "Bind user " << static_cast<size_t>(intercepter.user) << " action "
                                << static_cast<size_t>(intercepter.action) << " to key " << static_cast<size_t>(key);
                        });
                        users[game::User::UserId::User1].getKeybinds().setKeyboardBinding(
                            key, intercepter.action, true);
                        users.updateActions(false);
                        entities.kill(id);
                        if (intercepter.callback)
                            intercepter.callback();
                    }
                } else {
                    raylib::core::Gamepad::Button btn = raylib::core::Gamepad::getButtonPressed();

                    if (static_cast<int>(btn) == -1)
                        continue;
                    auto &user = users[intercepter.user];
                    raylib::core::Gamepad gamepad(user.getGamepadId());

                    if (gamepad.isButtonDown(btn)) {
                        Logger::logger.log(Logger::Severity::Information, [&](auto &out) {
                            out << "Bind user " << static_cast<size_t>(intercepter.user) << " action "
                                << static_cast<size_t>(intercepter.action) << " to gamepad button "
                                << static_cast<size_t>(btn);
                        });
                        user.getKeybinds().setGamepadBinding(
                            game::settings::GamepadInput(btn), intercepter.action, true);
                        users.updateActions(false);
                        entities.kill(id);
                        if (intercepter.callback)
                            intercepter.callback();
                    }
                }
            }
        }
    };
} // namespace game::systems

#endif /* !KEYBINDINTERCEPT_HPP_ */
