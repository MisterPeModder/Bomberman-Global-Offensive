/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** DrawText
*/

#include "UpdateKeyboardInput.hpp"
#include "game/components/History.hpp"
#include "game/components/KeyboardInput.hpp"
#include "game/GameTimer.hpp"

#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Entities.hpp"

#include "raylib/core/Keyboard.hpp"
#include "raylib/core/Window.hpp"

#include "util/util.hpp"

#include <cmath>

namespace game::systems
{
    using Keyboard = raylib::core::Keyboard;

    void UpdateKeyboardInput::run(ecs::SystemData data)
    {
        auto &entities = data.getResource<ecs::Entities>();
        auto &inputs = data.getStorage<game::components::KeyboardInput>();
        auto histories = ecs::maybe(data.getStorage<game::components::History>());

        auto iter = ecs::join(entities, inputs, histories);

        auto begin = iter.begin();
        auto end = iter.end();
        auto firstSelected = std::find_if(begin, end, [](auto i) { return std::get<1>(i).focused; });

        if (firstSelected == end)
            return;

        auto [self, field, history] = *firstSelected;
        Keyboard::Key key;
        int codepoint;

        while ((key = Keyboard::getKeyPressed()) != Keyboard::Key::NONE) {
            if (Keyboard::isKeyDown(Keyboard::Key::LEFT_CONTROL)) {
                switch (key) {
                    case Keyboard::Key::A: field.selectAll(); break;
                    case Keyboard::Key::C: field.copyToClipboard(false); break;
                    case Keyboard::Key::X: field.copyToClipboard(true); break;
                    case Keyboard::Key::V: field.pasteFromClipboard(); break;
                    case Keyboard::Key::D: field.focused = false; break;
                    default: break;
                }
            } else if (key == Keyboard::Key::HOME) {
                // HOME (begin): move to the start of the contents

                field.setCursorPos({0, 0}, game::components::KeyboardInput::selectKeyDown());
            } else if (key == Keyboard::Key::END) {
                // END: move to the end of the contents

                field.setCursorPos({UINT_MAX, UINT_MAX}, game::components::KeyboardInput::selectKeyDown());
            } else if (key == Keyboard::Key::ENTER || key == Keyboard::Key::KP_ENTER) {
                // ENTER: Submit input
                // SHIFT+ENTER: New line

                if (game::components::KeyboardInput::selectKeyDown())
                    field.insertLine();
                else
                    field.submit(self, data, history);
            }
        }
        while ((codepoint = Keyboard::getCharPressed())) {
            field.moveCursor(
                util::insertUtf8Codepoint(field.contents[field.cursorPos.y], codepoint, field.cursorPos.x));
        }

        double elapsed = data.getResource<game::GameTimer>().elapsed();

        field.checkKeyRepeats(self, data, elapsed);
        field.cursorBlink = fmod(field.cursorBlink + elapsed, 1.0);
    }
} // namespace game::systems
