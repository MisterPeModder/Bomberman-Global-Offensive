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
#include "game/gui/components/Widget.hpp"

namespace game
{
    void InputManager::run(ecs::SystemData data)
    {
        Users &users = data.getResource<Users>();
        Users::ActionEvent event = users.getNextAction();

        while (event.action != GameAction::NONE) {
            handleEvent(event, data);
            event = users.getNextAction();
        }
    }

    void InputManager::handleEvent(const Users::ActionEvent &event, ecs::SystemData data)
    {
        auto optionnalWidgets = ecs::maybe(data.getStorage<gui::Widget>());

        for (auto [widget, controlable, entity] :
            ecs::join(optionnalWidgets, data.getStorage<Controlable>(), data.getResource<ecs::Entities>())) {
            /// This entity doesn't listen the sender of the event.
            if (controlable.userId != event.user)
                continue;
            /// The widget consumed the event.
            if (widget && widget->selected && widget->update(entity, data, event))
                return;
            /// The entity isn't a widget (or hasn't consumed the event) and has a custom callback.
            if (controlable.callback && controlable.callback(entity, data, event))
                return;
        }
    }

} // namespace game
