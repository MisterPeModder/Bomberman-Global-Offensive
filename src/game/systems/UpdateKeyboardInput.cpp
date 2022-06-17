/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** DrawText
*/

#include "UpdateKeyboardInput.hpp"
#include "game/components/History.hpp"
#include "game/components/KeyboardInput.hpp"

#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Entities.hpp"
#include "ecs/resource/Timer.hpp"

#include "raylib/core/Keyboard.hpp"
#include "raylib/core/Window.hpp"

#include "util/util.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <string>
#include <string_view>

namespace game::systems
{
    using Keyboard = raylib::core::Keyboard;

    void UpdateKeyboardInput::run(ecs::SystemData data)
    {
        auto &entities = data.getResource<ecs::Entities>();
        auto &inputs = data.getStorage<game::KeyboardInput>();
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
                if (key == Keyboard::Key::A) {
                    // CTRL-A: Select All

                    field.cursorPos = 0;
                    field.selectionPos = field.contents.size();
                } else if ((key == Keyboard::Key::C || key == Keyboard::Key::X) && field.hasSelection()) {
                    // CTRL-C/X: Copy selection to clipboard

                    auto [selectStart, selectEnd] = std::minmax(field.selectionPos, field.cursorPos);
                    std::string copied(field.contents.cbegin() + selectStart, field.contents.cbegin() + selectEnd);

                    raylib::core::Window::setClipboard(copied);
                    if (key == Keyboard::Key::C)
                        field.moveCursor(0, false);
                    else
                        field.eraseSelection();
                } else if (key == Keyboard::Key::V) {
                    // CTRL+V: Paste from clipboard

                    std::string_view pasted = raylib::core::Window::getClipboard();

                    if (field.hasSelection())
                        field.eraseSelection();
                    field.contents.insert(field.cursorPos, pasted);
                    field.moveCursor(pasted.size());
                } else if (key == Keyboard::Key::D) {
                    // CTRL+D: Close console

                    field.focused = false;
                }
            } else if (key == Keyboard::Key::HOME) {
                // HOME (begin): move to the start of the contents

                field.moveCursor(
                    -static_cast<int>(field.contents.size()), Keyboard::isKeyDown(Keyboard::Key::LEFT_SHIFT));
            } else if (key == Keyboard::Key::END) {
                // END: move to the end of the contents

                field.moveCursor(field.contents.size(), Keyboard::isKeyDown(Keyboard::Key::LEFT_SHIFT));
            } else if (key == Keyboard::Key::ENTER || key == Keyboard::Key::KP_ENTER) {
                // ENTER: submit input

                if (!field.contents.empty() && field.onSubmit(self, data, field.contents)) {
                    if (history != nullptr)
                        history->push(field.contents);
                    field.clear();
                }
            }
        }
        while ((codepoint = Keyboard::getCharPressed())) {
            field.moveCursor(util::insertUtf8Codepoint(field.contents, codepoint, field.cursorPos));
        }

        double elapsed = data.getResource<ecs::Timer>().elapsed();

        field.checkKeyRepeats(self, data, elapsed);
        field.cursorBlink = fmod(field.cursorBlink + elapsed, 1.0);
    }
} // namespace game::systems
