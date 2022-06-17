/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** DrawText
*/

#include "UpdateKeyboardInput.hpp"
#include "game/components/KeyboardInput.hpp"

#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Timer.hpp"

#include "raylib/core/Keyboard.hpp"

#include "logger/Logger.hpp"

#include "util/util.hpp"

#include <algorithm>
#include <cmath>
#include <functional>

namespace game::systems
{
    using Keyboard = raylib::core::Keyboard;

    void UpdateKeyboardInput::run(ecs::SystemData data)
    {
        auto iter = ecs::join(data.getStorage<game::KeyboardInput>());

        auto begin = iter.begin();
        auto end = iter.end();
        auto firstSelected = std::find_if(begin, end, [](auto i) { return std::get<0>(i).focused; });

        if (firstSelected == end)
            return;

        game::KeyboardInput &field = std::get<0>(*firstSelected);
        int codepoint;

        while ((codepoint = Keyboard::getCharPressed())) {
            util::pushUtf8Codepoint(field.contents, codepoint);
            field.moveCursor(1);
        }

        double elapsed = data.getResource<ecs::Timer>().elapsed();

        field.backspaceRepeat.check(elapsed, [&field]() {
            field.moveCursor(-1);
            util::popUtf8Codepoint(field.contents);
        });
        field.leftArrowRepeat.check(elapsed, [&field]() { field.moveCursor(-1); });
        field.rightArrowRepeat.check(elapsed, [&field]() { field.moveCursor(1); });

        field.cursorBlink = fmod(field.cursorBlink + elapsed, 1.0);
    }
} // namespace game::systems
