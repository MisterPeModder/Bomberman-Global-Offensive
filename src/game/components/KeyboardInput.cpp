/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** KeyboardInput
*/

#include "KeyboardInput.hpp"
#include "History.hpp"

#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Entities.hpp"
#include "ecs/resource/Timer.hpp"

#include "raylib/core/Color.hpp"
#include "raylib/core/Keyboard.hpp"

#include "util/util.hpp"

#include <algorithm>
#include <cctype>
#include <functional>

namespace game
{
    using Keyboard = raylib::core::Keyboard;

    KeyboardInput::KeyRepeat::KeyRepeat(raylib::core::Keyboard::Key key, Callback callback)
        : _key(key), _repeatCooldown(REPEAT_DELAY), _timeSinceRepeat(0.0), _callback(callback)
    {
    }

    void KeyboardInput::KeyRepeat::check(KeyboardInput &input, ecs::Entity id, ecs::SystemData data, double elapsed)
    {
        if (Keyboard::isKeyDown(this->_key))
            this->_timeSinceRepeat = std::min(100.0, this->_timeSinceRepeat + elapsed);
        else
            this->_timeSinceRepeat = 0;
        this->_repeatCooldown = std::max(0.0, this->_repeatCooldown - elapsed);

        if (Keyboard::isKeyPressed(this->_key) && this->_timeSinceRepeat < REPEAT_THRESHOLD) {
            this->_callback(input, id, data);
        } else if (Keyboard::isKeyDown(this->_key) && this->_timeSinceRepeat >= REPEAT_THRESHOLD
            && this->_repeatCooldown <= 0) {
            this->_callback(input, id, data);
            this->_repeatCooldown = REPEAT_DELAY;
        }
    }

    KeyboardInput::KeyboardInput(onSubmitCallback submitCallback)
        : onSubmit(submitCallback), contents(), cursorPos(0), selectionPos(0), focused(false), cursorBlink(0.0)
    {
        this->keyRepeats[0] = KeyRepeat(Keyboard::Key::BACKSPACE, [](auto &field, auto, auto) {
            if (field.hasSelection()) {
                field.eraseSelection();
            } else if (field.cursorPos > 0) {
                std::size_t removed = util::removeUtf8Codepoint(field.contents, field.cursorPos - 1).second;
                field.moveCursor(-static_cast<int>(removed));
            }
        });

        this->keyRepeats[1] = KeyRepeat(Keyboard::Key::DELETE, [](auto &field, auto, auto) {
            if (field.hasSelection()) {
                field.eraseSelection();
            } else if (field.cursorPos < field.contents.size()) {
                util::removeUtf8Codepoint(field.contents, field.cursorPos);
                field.moveCursor(0);
            }
        });

        this->keyRepeats[2] = KeyRepeat(Keyboard::Key::LEFT, [](auto &field, auto, auto) {
            if (Keyboard::isKeyDown(Keyboard::Key::LEFT_CONTROL))
                field.moveCursorToWord(-1, Keyboard::isKeyDown(Keyboard::Key::LEFT_SHIFT));
            else
                field.moveCursor(-1, Keyboard::isKeyDown(Keyboard::Key::LEFT_SHIFT));
        });

        this->keyRepeats[3] = KeyRepeat(Keyboard::Key::RIGHT, [](auto &field, auto, auto) {
            if (Keyboard::isKeyDown(Keyboard::Key::LEFT_CONTROL))
                field.moveCursorToWord(1, Keyboard::isKeyDown(Keyboard::Key::LEFT_SHIFT));
            else
                field.moveCursor(1, Keyboard::isKeyDown(Keyboard::Key::LEFT_SHIFT));
        });

        this->keyRepeats[4] =
            KeyRepeat(Keyboard::Key::UP, [](KeyboardInput &field, ecs::Entity entity, ecs::SystemData data) {
                auto &histories = data.getStorage<game::components::History>();

                if (histories.contains(entity.getId())) {
                    auto &history = histories[entity.getId()];

                    if (history.pos == 0)
                        history.savedCurrentEntry = field.contents;
                    history.moveUp();
                    history.load(field.contents);
                    field.moveCursor(field.contents.size());
                }
            });

        this->keyRepeats[5] =
            KeyRepeat(Keyboard::Key::DOWN, [](KeyboardInput &field, ecs::Entity entity, ecs::SystemData data) {
                auto &histories = data.getStorage<game::components::History>();

                if (histories.contains(entity.getId())) {
                    auto &history = histories[entity.getId()];

                    history.moveDown();
                    history.load(field.contents);
                    field.moveCursor(field.contents.size());
                }
            });
    }

    void KeyboardInput::moveCursor(int offset, bool selectingText)
    {
        std::size_t &pos = selectingText ? this->selectionPos : this->cursorPos;
        std::size_t oldPos = pos;

        if (offset < 0) {
            pos -= std::min(pos, static_cast<std::size_t>(-offset));
            pos = util::utf8BoundaryStart(this->contents, pos);
        } else {
            pos = std::min(this->contents.size(), pos + static_cast<std::size_t>(offset));
            pos = util::utf8BoundaryEnd(this->contents, pos);
        }
        if (oldPos != pos)
            this->cursorBlink = 0.0;
        if (!selectingText)
            this->selectionPos = this->cursorPos;
    }

    void KeyboardInput::moveCursorToWord(int wordOffset, bool selectingText)
    {
        std::size_t pos = selectingText ? this->selectionPos : this->cursorPos;
        int offset = 0;

        if (!this->contents.empty()) {
            if (wordOffset > 0) {
                while (pos + offset < this->contents.size() && std::isalnum(this->contents[pos + offset]))
                    ++offset;
                while (pos + offset < this->contents.size() && !std::isalnum(this->contents[pos + offset]))
                    ++offset;
            } else if (wordOffset < 0) {
                while (pos - offset > 0 && std::isalnum(this->contents[pos - offset - 1]))
                    ++offset;
                while (pos - offset > 0 && !std::isalnum(this->contents[pos - offset - 1]))
                    ++offset;
                offset = -offset;
            }
        }
        this->moveCursor(offset, selectingText);
    }

    KeyboardInput::CursorType KeyboardInput::getCursorType()
    {
        if (this->focused && this->cursorBlink < 0.5 && !this->hasSelection())
            return CursorType::BEAM;
        return CursorType::NONE;
    }

    bool KeyboardInput::hasSelection() noexcept { return this->selectionPos != this->cursorPos; }

    void KeyboardInput::eraseSelection()
    {
        auto [selectStart, selectEnd] = std::minmax(this->selectionPos, this->cursorPos);

        this->contents.erase(this->contents.cbegin() + selectStart, this->contents.cbegin() + selectEnd);
        this->cursorPos = selectStart;
        this->selectionPos = selectStart;
    }

    void KeyboardInput::clear()
    {
        this->contents.clear();
        this->cursorPos = 0;
        this->selectionPos = 0;
    }

    void KeyboardInput::checkKeyRepeats(ecs::Entity id, ecs::SystemData data, double elapsed)
    {
        for (auto &keyRepeat : this->keyRepeats)
            keyRepeat.check(*this, id, data, elapsed);
    }
} // namespace game
