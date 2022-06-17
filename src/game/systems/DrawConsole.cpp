/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Draw Console
*/

#include "DrawConsole.hpp"

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"

#include "game/components/KeyboardInput.hpp"
#include "game/components/Position.hpp"
#include "game/components/Size2D.hpp"
#include "game/gui/components/Console.hpp"

#include "raylib/core/Color.hpp"
#include "raylib/core/Vector2.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/shapes/Rectangle.hpp"
#include "raylib/text/Font.hpp"

#include <string>

namespace game::systems
{
    static constexpr raylib::core::Color outputColor(game::gui::Console const &console)
    {
        switch (console.outputSeverity) {
            case Logger::Severity::Debug: return raylib::core::Color::SKY_BLUE;
            case Logger::Severity::Error: return raylib::core::Color::RED;
            case Logger::Severity::Warning: return raylib::core::Color::YELLOW;
            default: return raylib::core::Color::GRAY;
        }
    }

    void DrawConsole::run(ecs::SystemData data)
    {
        using Color = raylib::core::Color;
        using Vector2f = raylib::core::Vector2f;

        auto &consoles = data.getStorage<game::gui::Console>();
        auto &positions = data.getStorage<game::components::Position>();
        auto &sizes = data.getStorage<game::components::Size2D>();
        auto &fields = data.getStorage<game::KeyboardInput>();

        auto join = ecs::join(consoles, positions, sizes, fields);

        // If the console does not exist (somehow), do nothing
        if (join.begin() == join.end())
            return;

        auto [console, pos, size, field] = *join.begin();

        // Hide the console when its input is not in focus
        if (!field.focused)
            return;

        std::string text = ">>> " + field.contents;
        std::string outputText = "- " + console.output;
        std::string textBeforeCursor(text.cbegin(), text.cbegin() + 4 + field.cursorPos);

        Vector2f textSize = console.font.measure(text, 20);
        Vector2f textbeforeCursorSize = console.font.measure(textBeforeCursor, 20);
        Vector2f outputSize = console.font.measure(outputText, 20);

        float border = 2.0f;
        float padding = 10.0f;
        float lineSpacing = 5.0f;
        int lineCount = console.output.empty() ? 1 : 2;

        // Position the console at the bottom of the screen
        pos.x = 0;
        pos.y = raylib::core::Window::getHeight() - size.y;

        // Occupy the full window width and enough height for two lines and some padding
        size.x = raylib::core::Window::getWidth();
        size.y = textSize.y + outputSize.y + lineCount * border + lineCount * padding + lineSpacing;

        Vector2f drawPos{pos.x, pos.y};
        Vector2f inputPos{drawPos.x + border + padding, drawPos.y + padding};

        raylib::shapes::Rectangle background(drawPos, size, Color::BLACK);

        background.draw();
        background.setColor(Color::WHITE);

        // Draw selection box
        if (field.hasSelection()) {
            auto [selectStart, selectEnd] = std::minmax(field.selectionPos, field.cursorPos);
            auto startIter = text.cbegin() + 4 + selectStart;
            auto endIter = text.cbegin() + 4 + selectEnd;

            Vector2f sizeBeforeSelect = console.font.measure(std::string(text.cbegin(), startIter), 20);
            Vector2f selectSize = console.font.measure(std::string(startIter, endIter), 20);

            raylib::shapes::Rectangle selection(
                {inputPos.x + sizeBeforeSelect.x, inputPos.y}, {selectSize.x, textSize.y}, Color::BLUE);

            selection.draw();
        }

        background.drawLines(border);

        console.font.draw(text, inputPos, 20, Color::WHITE);

        // Draw output
        if (!console.output.empty()) {
            console.font.draw(outputText, drawPos + Vector2f{border + padding, textSize.y + padding + lineSpacing}, 20,
                outputColor(console));
        }

        // Draw cursor
        if (field.getCursorType() != game::KeyboardInput::CursorType::NONE) {
            raylib::shapes::Rectangle cursor(
                inputPos + Vector2f{textbeforeCursorSize.x, 0}, Vector2f{1, textSize.y}, Color::WHITE);

            cursor.draw();
        }
    }

} // namespace game::systems
