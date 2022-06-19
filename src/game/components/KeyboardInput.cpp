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
#include "raylib/core/Window.hpp"

#include "util/util.hpp"

#include <algorithm>
#include <cctype>
#include <functional>
#include <tuple>

using raylib::core::Vector2u;

namespace game::components
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
        : onSubmit(submitCallback), contents{""}, cursorPos(0, 0), selectionPos(0, 0), focused(false), cursorBlink(0.0)
    {
        this->keyRepeats[0] =
            KeyRepeat(Keyboard::Key::BACKSPACE, [](auto &field, auto, auto) { field.deleteBackwards(); });

        this->keyRepeats[1] = KeyRepeat(Keyboard::Key::DELETE, [](auto &field, auto, auto) { field.deleteForwards(); });

        this->keyRepeats[2] = KeyRepeat(Keyboard::Key::LEFT, [](auto &field, auto, auto) {
            bool shiftPressed = selectKeyDown();

            if (Keyboard::isKeyDown(Keyboard::Key::LEFT_CONTROL))
                field.moveCursorToWord(-1, selectKeyDown());
            else if (!field.hasSelection() || shiftPressed)
                field.moveCursor(-1, shiftPressed);
            else
                field.setCursorPos(field.getSelection().first);
        });

        this->keyRepeats[3] = KeyRepeat(Keyboard::Key::RIGHT, [](auto &field, auto, auto) {
            bool shiftPressed = selectKeyDown();

            if (Keyboard::isKeyDown(Keyboard::Key::LEFT_CONTROL))
                field.moveCursorToWord(1, selectKeyDown());
            else if (!field.hasSelection() || shiftPressed)
                field.moveCursor(1, shiftPressed);
            else
                field.setCursorPos(field.getSelection().second);
        });

        this->keyRepeats[4] =
            KeyRepeat(Keyboard::Key::UP, [](KeyboardInput &field, ecs::Entity entity, ecs::SystemData data) {
                if (!field.hasSelection() && field.cursorPos.y == 0) {
                    auto &histories = data.getStorage<game::components::History>();

                    if (histories.contains(entity.getId()))
                        field.prevHistory(histories[entity.getId()]);
                } else {
                    auto pos = field.hasSelection() ? field.getSelection().first : field.cursorPos;
                    field.setCursorPos(Vector2u(pos.x, pos.y > 0 ? pos.y - 1 : 0), selectKeyDown());
                }
            });

        this->keyRepeats[5] =
            KeyRepeat(Keyboard::Key::DOWN, [](KeyboardInput &field, ecs::Entity entity, ecs::SystemData data) {
                if (!field.hasSelection() && field.cursorPos.y + 1 >= field.contents.size()) {
                    auto &histories = data.getStorage<game::components::History>();

                    if (histories.contains(entity.getId()))
                        field.nextHistory(histories[entity.getId()]);
                } else {
                    auto pos = field.hasSelection() ? field.getSelection().second : field.cursorPos;
                    field.setCursorPos(
                        Vector2u(pos.x, std::min(static_cast<std::size_t>(pos.y + 1), field.contents.size() - 1)),
                        selectKeyDown());
                }
            });
    }

    std::pair<raylib::core::Vector2u, raylib::core::Vector2u> KeyboardInput::getSelection() const noexcept
    {
        if (this->selectionPos.y > this->cursorPos.y) {
            return {this->cursorPos, this->selectionPos};
        } else if (this->selectionPos.y < this->cursorPos.y) {
            return {this->selectionPos, this->cursorPos};
        } else if (this->selectionPos.x > this->cursorPos.x) {
            return {this->cursorPos, this->selectionPos};
        } else {
            return {this->selectionPos, this->cursorPos};
        }
    }

    void KeyboardInput::moveCursor(int offset, bool selectingText)
    {
        if (this->contents.empty())
            return;

        Vector2u pos = selectingText ? this->selectionPos : this->cursorPos;

        // normalize cursor height
        if (pos.y >= this->contents.size())
            pos.y = this->contents.size() - 1;

        if (offset < 0) {
            if (pos.x == 0 && pos.y > 0) {
                pos = Vector2u(this->contents[pos.y - 1].size(), pos.y - 1);
            } else if (pos.x != 0) {
                pos.x -= std::min(pos.x, static_cast<unsigned int>(-offset));
                pos.x = util::utf8BoundaryStart(this->contents[pos.y], pos.x);
            }
        } else {
            if (pos.x >= this->contents[pos.y].size() && pos.y + 1 < this->contents.size()) {
                pos = Vector2u(0, pos.y + 1);
            } else {
                pos.x = std::min(this->contents[pos.y].size(), pos.x + static_cast<std::size_t>(offset));
                pos.x = util::utf8BoundaryEnd(this->contents[pos.y], pos.x);
            }
        }

        this->setCursorPos(pos, selectingText);
    }

    void KeyboardInput::moveCursorToWord(int wordOffset, bool selectingText)
    {
        Vector2u pos = selectingText ? this->selectionPos : this->cursorPos;
        int offset = 0;

        if (!this->contents.empty() && !this->contents[pos.y].empty()) {
            std::string const &line = this->contents[pos.y];

            if (wordOffset > 0) {
                while (pos.x + offset < line.size() && std::isalnum(line[pos.x + offset]))
                    ++offset;
                while (pos.x + offset < line.size() && !std::isalnum(line[pos.x + offset]))
                    ++offset;
            } else if (wordOffset < 0) {
                while (pos.x - offset > 0 && std::isalnum(line[pos.x - offset - 1]))
                    ++offset;
                while (pos.x - offset > 0 && !std::isalnum(line[pos.x - offset - 1]))
                    ++offset;
                offset = -offset;
            }
        }
        this->moveCursor(offset, selectingText);
    }

    void KeyboardInput::setCursorPos(raylib::core::Vector2u newPos, bool selectingText) noexcept
    {
        Vector2u &pos = selectingText ? this->selectionPos : this->cursorPos;
        Vector2u oldPos = pos;

        pos.y = std::min(this->contents.size() - 1, static_cast<std::size_t>(newPos.y));
        pos.x = std::min(this->contents[pos.y].size(), static_cast<std::size_t>(newPos.x));
        pos.x = util::utf8BoundaryStart(this->contents[pos.y], pos.x);

        if (oldPos != pos)
            this->cursorBlink = 0.0;
        if (!selectingText)
            this->selectionPos = this->cursorPos;
    }

    KeyboardInput::CursorType KeyboardInput::getCursorType()
    {
        if (this->focused && this->cursorBlink < 0.5 && !this->hasSelection())
            return CursorType::BEAM;
        return CursorType::NONE;
    }

    bool KeyboardInput::hasSelection() const noexcept { return this->selectionPos != this->cursorPos; }

    void KeyboardInput::eraseSelection()
    {
        auto [selectStart, selectEnd] = this->getSelection();
        unsigned int lineCount = selectEnd.y - selectStart.y;
        std::string &firstLine = this->contents[selectStart.y];

        this->cursorPos = selectStart;
        this->selectionPos = selectStart;
        if (lineCount == 0) {
            firstLine.erase(firstLine.cbegin() + selectStart.x, firstLine.cbegin() + selectEnd.x);
            return;
        }
        std::string &lastLine = this->contents[selectEnd.y];

        firstLine.erase(firstLine.cbegin() + selectStart.x, firstLine.cend());

        if (selectEnd.x >= lastLine.size())
            this->contents.erase(this->contents.cbegin() + selectEnd.y);
        else
            lastLine.erase(lastLine.cbegin(), lastLine.cbegin() + selectEnd.x);

        if (lineCount > 1)
            this->contents.erase(this->contents.cbegin() + selectStart.y + 1, this->contents.cbegin() + selectEnd.y);
    }

    void KeyboardInput::clear()
    {
        this->contents.clear();
        this->contents.emplace_back();
        this->cursorPos = 0;
        this->selectionPos = 0;
    }

    void KeyboardInput::checkKeyRepeats(ecs::Entity id, ecs::SystemData data, double elapsed)
    {
        for (auto &keyRepeat : this->keyRepeats)
            keyRepeat.check(*this, id, data, elapsed);
    }

    std::string KeyboardInput::mergeContents() const
    {
        std::string result;
        auto it = this->contents.cbegin();
        auto end = this->contents.cend();

        if (it != end) {
            result.append(*it);
            ++it;
        }
        while (it != end) {
            result.push_back('\n');
            result.append(*it);
            ++it;
        }
        return result;
    }

    void KeyboardInput::unmergeContents(std::string_view merged)
    {
        this->contents.clear();
        auto end = merged.cend();
        auto it = std::find(merged.cbegin(), end, '\n');

        this->contents.emplace_back(merged.begin(), it);
        while (it != end) {
            auto next = std::find(++it, end, '\n');
            this->contents.emplace_back(it, next);
            it = next;
        }
    }

    void KeyboardInput::selectAll()
    {
        this->cursorPos = {0, 0};
        this->selectionPos.y = this->contents.size() - 1;
        this->selectionPos.x = this->contents[this->selectionPos.y].size();
    }

    void KeyboardInput::copyToClipboard(bool doCut)
    {
        if (!this->hasSelection())
            return;

        auto [selectStart, selectEnd] = this->getSelection();
        std::string copied;

        for (std::size_t lineY = selectStart.y; lineY <= selectEnd.y; ++lineY) {
            std::string const &line = this->contents[lineY];

            auto start = line.cbegin() + (lineY == selectStart.y ? selectStart.x : 0);
            auto end = line.cbegin() + (lineY == selectEnd.y ? selectEnd.x : line.size());

            if (lineY > 0)
                copied.push_back('\n');
            copied.append(start, end);
        }

        raylib::core::Window::setClipboard(copied);
        if (doCut)
            this->eraseSelection();
        else
            this->moveCursor(0, false);
    }

    void KeyboardInput::pasteFromClipboard()
    {
        std::string_view pasted = raylib::core::Window::getClipboard();

        if (this->hasSelection())
            this->eraseSelection();

        auto end = pasted.cend();
        auto it = std::find(pasted.cbegin(), end, '\n');

        std::size_t startY = this->cursorPos.y;

        this->contents[startY].insert(this->contents[startY].cbegin() + this->cursorPos.x, pasted.cbegin(), it);

        size_t firstPasteLineSize = it - pasted.cbegin();
        size_t firstPasteLineEnd = this->cursorPos.x + firstPasteLineSize;
        this->setCursorPos({static_cast<unsigned int>(firstPasteLineEnd), cursorPos.y});

        for (std::size_t lineY = this->cursorPos.y; it != end; ++lineY) {
            auto next = std::find(++it, end, '\n');
            if (next != end) {
                this->contents.emplace(this->contents.cbegin() + lineY + 1, it, next);
            } else {
                if (lineY + 1 >= this->contents.size())
                    this->contents.emplace_back();
                this->contents[lineY + 1].insert(this->contents[lineY + 1].cbegin(), it, next);

                size_t lastPasteLineSize = next - it;

                this->setCursorPos(
                    {static_cast<unsigned int>(lastPasteLineSize), static_cast<unsigned int>(lineY + 1)});

                auto rest = this->contents[startY].cbegin() + firstPasteLineEnd;
                this->contents[lineY + 1].insert(
                    this->contents[lineY + 1].cbegin() + lastPasteLineSize, rest, this->contents[startY].cend());
                this->contents[startY].erase(rest, this->contents[startY].cend());
            }
            it = next;
        }
    }

    void KeyboardInput::insertLine()
    {
        std::string &line = this->contents[this->cursorPos.y];
        std::string newLine(line.cbegin() + this->cursorPos.x, line.cend());
        line.erase(line.cbegin() + this->cursorPos.x, line.cend());

        this->contents.insert(this->contents.cbegin() + this->cursorPos.y + 1, std::move(newLine));
        this->moveCursor(1);
    }

    void KeyboardInput::submit(ecs::Entity self, ecs::SystemData data, game::components::History *history)
    {
        std::string input = this->mergeContents();

        if (!input.empty() && this->onSubmit(self, data, input)) {
            if (history != nullptr)
                history->push(input);
            this->clear();
        }
    }

    bool KeyboardInput::selectKeyDown()
    {
        return Keyboard::isKeyDown(Keyboard::Key::LEFT_SHIFT) || Keyboard::isKeyDown(Keyboard::Key::RIGHT_SHIFT);
    }

    void KeyboardInput::deleteBackwards()
    {
        if (this->hasSelection()) {
            this->eraseSelection();
            return;
        }
        Vector2u pos = this->cursorPos;

        if (this->contents.empty() || pos == Vector2u(0, 0))
            return; // cannot remove backwards from beginning

        if (pos.x == 0) {
            this->moveCursor(-1);
            this->contents[pos.y - 1].append(this->contents[pos.y]);
            this->contents.erase(this->contents.begin() + pos.y);
        } else {
            std::size_t removed = util::removeUtf8Codepoint(this->contents[pos.y], pos.x - 1).second;
            this->moveCursor(-static_cast<int>(removed));
        }
    }

    void KeyboardInput::deleteForwards()
    {
        if (this->hasSelection()) {
            this->eraseSelection();
            return;
        }
        Vector2u pos = this->cursorPos;

        // do nothing when ...
        if (this->contents.empty()            // ...field has no contents...
            || pos.y >= this->contents.size() // ...cursor Y is beyond the number of lines...
            || (pos.y + 1 == this->contents.size()
                && pos.x >= this->contents[pos.y].size())) // ...cursor is past the last char.
            return;

        std::string const &currentLine = this->contents[pos.y];

        if (pos.y + 1 < this->contents.size() && pos.x >= currentLine.size()) {
            this->moveCursor(1);
            this->contents[pos.y + 1].append(currentLine);
            this->contents.erase(this->contents.begin() + pos.y);
        } else {
            util::removeUtf8Codepoint(this->contents[pos.y], pos.x);
            this->moveCursor(0);
        }
    }

    void KeyboardInput::prevHistory(History &history)
    {
        if (history.pos == 0)
            history.savedCurrentEntry = this->mergeContents();
        history.moveUp();
        std::string const &entry = history.get();
        this->unmergeContents(entry);
        this->setCursorPos(Vector2u(0, 0));
    }

    void KeyboardInput::nextHistory(History &history)
    {
        history.moveDown();
        std::string const &entry = history.get();
        this->unmergeContents(entry);
        this->setCursorPos(Vector2u(this->contents[this->contents.size() - 1].size(), this->contents.size() - 1));
    }
} // namespace game::components
