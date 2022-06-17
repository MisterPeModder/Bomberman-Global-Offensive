/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** KeyboardInput
*/

#include "KeyboardInput.hpp"

#include "raylib/core/Color.hpp"
#include "raylib/core/Keyboard.hpp"

#include "util/util.hpp"

#include <algorithm>
#include <cctype>
#include <functional>

namespace game
{
    using Keyboard = raylib::core::Keyboard;

    KeyboardInput::KeyRepeat::KeyRepeat(raylib::core::Keyboard::Key key)
        : _key(key), _repeatCooldown(REPEAT_DELAY), _timeSinceRepeat(0.0)
    {
    }

    void KeyboardInput::KeyRepeat::check(double elapsed, std::function<void()> onRepeat)
    {
        if (Keyboard::isKeyDown(this->_key))
            this->_timeSinceRepeat = std::min(100.0, this->_timeSinceRepeat + elapsed);
        else
            this->_timeSinceRepeat = 0;
        this->_repeatCooldown = std::max(0.0, this->_repeatCooldown - elapsed);

        if (Keyboard::isKeyPressed(this->_key) && this->_timeSinceRepeat < REPEAT_THRESHOLD) {
            onRepeat();
        } else if (Keyboard::isKeyDown(this->_key) && this->_timeSinceRepeat >= REPEAT_THRESHOLD
            && this->_repeatCooldown <= 0) {
            onRepeat();
            this->_repeatCooldown = REPEAT_DELAY;
        }
    }

    KeyboardInput::KeyboardInput(std::string &&initialContents, bool pFocused)
        : contents(initialContents), cursorPos(0), selectionPos(0), focused(pFocused),
          backspaceRepeat(Keyboard::Key::BACKSPACE), deleteRepeat(Keyboard::Key::DELETE),
          leftArrowRepeat(Keyboard::Key::LEFT), rightArrowRepeat(Keyboard::Key::RIGHT), cursorBlink(0.0)
    {
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

    void KeyboardInput::eraseSelection() noexcept
    {
        auto [selectStart, selectEnd] = std::minmax(this->selectionPos, this->cursorPos);

        this->contents.erase(this->contents.cbegin() + selectStart, this->contents.cbegin() + selectEnd);
        this->cursorPos = selectStart;
        this->selectionPos = selectStart;
    }
} // namespace game
