/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Console
*/

#include "Console.hpp"
#include "ecs/Storage.hpp"
#include "util/util.hpp"

#include "game/components/KeyboardInput.hpp"

namespace game ::gui
{
    Console::Console() : font(util::makePath("assets", "fonts", "Inconsolata-Medium.ttf"), 20, nullptr, 65535) {}

    bool Console::handleInput(ecs::Entity self, ecs::SystemData data, game::Users::ActionEvent const &event)
    {
        if (event.action == GameAction::TOGGLE_CONSOLE && event.value > 0.f) {
            game::KeyboardInput &input = data.getStorage<game::KeyboardInput>()[self.getId()];
            input.focused = !input.focused;
            return true;
        }
        return false;
    }
} // namespace game::gui
