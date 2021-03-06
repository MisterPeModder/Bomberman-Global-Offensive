/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** DrawText
*/

#include "InputManager.hpp"
#include "components/Controlable.hpp"
#include "ecs/join.hpp"
#include "game/Engine.hpp"
#include "game/components/KeybindIntercepter.hpp"
#include "game/components/KeyboardInput.hpp"
#include "game/gui/components/Widget.hpp"

#include <algorithm>

using namespace game::components;

namespace game::systems
{
    void InputManager::run(ecs::SystemData data)
    {
        if (data.getStorage<KeybindIntercepter>().size() > 0)
            return;
        auto inputs = ecs::join(data.getStorage<game::components::KeyboardInput>());
        bool hasActiveInput = std::any_of(inputs.begin(), inputs.end(), [](auto i) { return std::get<0>(i).focused; });

        Users &users = data.getResource<game::resources::EngineResource>().engine->getUsers();
        users.setIgnoreKeyboard(hasActiveInput);
        Users::ActionEvent event = users.getNextAction();

        while (event.action != GameAction::NONE) {
            handleEvent(event, data);
            event = users.getNextAction();
        }
    }

    void InputManager::handleEvent(const Users::ActionEvent &event, ecs::SystemData data)
    {
        auto optionalWidgets = ecs::maybe(data.getStorage<gui::Widget>());

        for (auto [widget, controlable, entity] :
            ecs::join(optionalWidgets, data.getStorage<Controlable>(), data.getResource<ecs::Entities>())) {
            /// This entity doesn't listen the sender of the event.
            if (controlable.userId != event.user && controlable.userId != User::UserId::AllUsers)
                continue;
            /// The widget consumed the event.
            if (widget && widget->selected && widget->update(entity, data, event))
                return;
            /// The entity isn't a widget (or hasn't consumed the event) and has a custom callback.
            if (controlable.callback && controlable.callback(entity, data, event))
                return;
        }
    }

} // namespace game::systems
