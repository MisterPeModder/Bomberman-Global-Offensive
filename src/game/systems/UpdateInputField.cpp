/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** DrawText
*/

#include "UpdateInputField.hpp"
#include "game/gui/components/InputField.hpp"

#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Timer.hpp"

#include "raylib/core/Keyboard.hpp"

#include "logger/Logger.hpp"

#include "util/util.hpp"

#include <algorithm>

namespace game::systems
{
    void UpdateInputField::run(ecs::SystemData data)
    {
        using Keyboard = raylib::core::Keyboard;

        auto iter = ecs::join(data.getStorage<game::gui::InputField>());

        auto begin = iter.begin();
        auto end = iter.end();
        auto firstSelected = std::find_if(begin, end, [](auto i) { return std::get<0>(i).selected; });

        if (firstSelected == end)
            return;

        game::gui::InputField &field = std::get<0>(*firstSelected);
        int codepoint;

        while ((codepoint = Keyboard::getCharPressed()))
            util::pushUtf8Codepoint(field.contents, codepoint);

        if (field.backspaceCooldown <= 0) { // if cooldown is zero, accept backspace event
            if (Keyboard::isKeyDown(Keyboard::Key::BACKSPACE)) {
                util::popUtf8Codepoint(field.contents);
                field.backspaceCooldown = game::gui::InputField::BACKSPACE_DELAY;
            }
        } else { // or else, tick down to cooldown
            auto &timer = data.getResource<ecs::Timer>();

            field.backspaceCooldown = std::max(0.0, field.backspaceCooldown - timer.elapsed());
        }

        Logger::logger.log(
            Logger::Severity::Debug, [&](auto &out) { out << "Field contents: [[" << field.contents << "]]"; });
    }
} // namespace game::systems
