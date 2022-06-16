/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** DrawText
*/

#include "UpdateInputField.hpp"
#include "game/components/KeyboardInput.hpp"

#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Timer.hpp"

#include "raylib/core/Keyboard.hpp"

#include "logger/Logger.hpp"

#include "util/util.hpp"

#include <algorithm>

namespace game::systems
{
    using Keyboard = raylib::core::Keyboard;

    static void handleFieldBackspace(game::KeyboardInput &field, ecs::Timer const &timer)
    {
        if (Keyboard::isKeyDown(Keyboard::Key::BACKSPACE))
            field.timeSinceBackspace = std::min(100.0, field.timeSinceBackspace + timer.elapsed());
        else
            field.timeSinceBackspace = 0;
        field.backspaceCooldown = std::max(0.0, field.backspaceCooldown - timer.elapsed());

        if (Keyboard::isKeyPressed(Keyboard::Key::BACKSPACE)
            && field.timeSinceBackspace < game::KeyboardInput::BACKSPACE_REPEAT_THRESHOLD) {
            util::popUtf8Codepoint(field.contents);
        } else if (Keyboard::isKeyDown(Keyboard::Key::BACKSPACE)
            && field.timeSinceBackspace >= game::KeyboardInput::BACKSPACE_REPEAT_THRESHOLD
            && field.backspaceCooldown <= 0) {
            util::popUtf8Codepoint(field.contents);
            field.backspaceCooldown = game::KeyboardInput::BACKSPACE_REPEAT_DELAY;
        }
    }

    void UpdateInputField::run(ecs::SystemData data)
    {
        auto iter = ecs::join(data.getStorage<game::KeyboardInput>());

        auto begin = iter.begin();
        auto end = iter.end();
        auto firstSelected = std::find_if(begin, end, [](auto i) { return std::get<0>(i).focused; });

        if (firstSelected == end)
            return;

        game::KeyboardInput &field = std::get<0>(*firstSelected);
        int codepoint;

        while ((codepoint = Keyboard::getCharPressed()))
            util::pushUtf8Codepoint(field.contents, codepoint);
        handleFieldBackspace(field, data.getResource<ecs::Timer>());

        Logger::logger.log(Logger::Severity::Debug, [&](auto &out) {
            out << "Field contents: [[" << field.contents << "]], since backspace: " << field.timeSinceBackspace
                << ", cooldown: " << field.backspaceCooldown;
        });
    }
} // namespace game::systems
