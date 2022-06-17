/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** KeyboardInput
*/

#include "KeyboardInput.hpp"

#include "raylib/core/Color.hpp"
#include "raylib/core/Keyboard.hpp"

#include <algorithm>
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
        : contents(initialContents), cursorPos(0), focused(pFocused), backspaceRepeat(Keyboard::Key::BACKSPACE),
          leftArrowRepeat(Keyboard::Key::LEFT), rightArrowRepeat(Keyboard::Key::RIGHT), cursorBlink(0.0)
    {
    }

    void KeyboardInput::moveCursor(int offset)
    {
        std::size_t oldPos = this->cursorPos;

        if (offset < 0)
            this->cursorPos -= std::min(this->cursorPos, static_cast<std::size_t>(-offset));
        else
            this->cursorPos = std::min(this->contents.size(), this->cursorPos + static_cast<std::size_t>(offset));
        if (oldPos != this->cursorPos)
            this->cursorBlink = 0.0;
    }

    KeyboardInput::CursorType KeyboardInput::getCursorType()
    {
        if (this->focused && this->cursorBlink < 0.5)
            return CursorType::BEAM;
        return CursorType::NONE;
    };
} // namespace game
