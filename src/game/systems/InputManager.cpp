/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** DrawText
*/

#include "InputManager.hpp"
#include "components/Controlable.hpp"
#include "ecs/Storage.hpp"
#include "ecs/World.hpp"
#include "ecs/join.hpp"
#include "ecs/system/SystemData.hpp"
#include "game/Users.hpp"

#include "logger/Logger.hpp"

namespace game
{
    void InputManager::run(ecs::SystemData data)
    {
        Users &users = data.getResource<Users>();
        Users::ActionEvent event = users.getNextAction();

        while (event.action != GameAction::NONE) {
            Logger::logger.log(Logger::Severity::Debug, [&](std::ostream &writer) {
                writer << "Action " << static_cast<size_t>(event.action) << " with value " << event.value
                       << " from user " << static_cast<size_t>(event.user);
            });
            handleEvent(event, data);
            event = users.getNextAction();
        }
    }

    void InputManager::handleEvent(const Users::ActionEvent &event, ecs::SystemData data)
    {
        for (auto [controlable] : ecs::join(data.getStorage<Controlable>()))
            if (controlable.userId == event.user && controlable.callback && controlable.callback(event))
                return;
    }
} // namespace game
