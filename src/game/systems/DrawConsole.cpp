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
#include <utility>

namespace game::systems
{
    using game::gui::Console;
    using raylib::core::Color;
    using raylib::core::Vector2f;

    struct RenderedText {
        std::string value;
        std::vector<std::size_t> lineOffsets;
    };

    static RenderedText renderText(game::components::KeyboardInput const &field)
    {
        RenderedText text{">>> " + field.contents[0], std::vector<std::size_t>()};
        std::size_t currentOffset = text.value.size();

        text.lineOffsets.resize(field.contents.size(), 0);
        for (std::size_t i = 1; i < field.contents.size(); ++i) {
            text.value.push_back('\n');
            text.value.append("... ");
            text.value.append(field.contents[i]);
            text.lineOffsets[i] = currentOffset + 1;
            currentOffset += 5 + field.contents[i].size();
        }
        return text;
    }

    static void renderSelection(Vector2f pos, game::components::KeyboardInput const &field,
        game::gui::Console const &console, RenderedText const &rendered)
    {
        if (!field.hasSelection())
            return;
        auto const &[text, lineOffsets] = rendered;
        auto [selectStart, selectEnd] = field.getSelection();

        float lineOffset = static_cast<float>(Console::FONT_HEIGHT) + static_cast<float>(Console::FONT_HEIGHT) / 2;

        for (std::size_t lineY = selectStart.y; lineY <= selectEnd.y; ++lineY) {
            std::size_t lineStartOffset = lineOffsets[lineY];

            auto startIter = text.cbegin() + lineStartOffset + 4 + (lineY == selectStart.y ? selectStart.x : 0);
            auto endIter = text.cbegin() + lineStartOffset + 4
                + (lineY == selectEnd.y ? selectEnd.x : field.contents[lineY].size());

            Vector2f sizeBeforeSelect =
                console.font.measure(std::string(text.cbegin() + lineStartOffset, startIter), Console::FONT_HEIGHT);
            Vector2f selectSize = console.font.measure(std::string(startIter, endIter), Console::FONT_HEIGHT);

            raylib::shapes::Rectangle::draw(
                {pos.x + sizeBeforeSelect.x, pos.y + lineOffset * static_cast<float>(lineY)},
                {selectSize.x, Console::FONT_HEIGHT}, Color::BLUE);
        }
    }

    static constexpr raylib::core::Color outputColor(Console const &console)
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
        auto &consoles = data.getStorage<Console>();
        auto &positions = data.getStorage<game::components::Position>();
        auto &sizes = data.getStorage<game::components::Size2D>();
        auto &fields = data.getStorage<game::components::KeyboardInput>();

        auto join = ecs::join(consoles, positions, sizes, fields);

        // If the console does not exist (somehow), do nothing
        if (join.begin() == join.end())
            return;

        auto [console, pos, size, field] = *join.begin();

        // Hide the console when its input is not in focus
        if (!field.focused)
            return;

        RenderedText rendered(renderText(field));
        auto const &[text, lineOffsets] = rendered;

        std::string outputText = "- " + console.output;
        std::string textBeforeCursor(text.cbegin() + lineOffsets[field.cursorPos.y],
            text.cbegin() + lineOffsets[field.cursorPos.y] + 4 + field.cursorPos.x);

        Vector2f textSize = console.font.measure(text, Console::FONT_HEIGHT);
        Vector2f textbeforeCursorSize = console.font.measure(textBeforeCursor, Console::FONT_HEIGHT);
        Vector2f outputSize = console.font.measure(outputText, Console::FONT_HEIGHT);

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

        // Draw the console box, with outlines
        raylib::shapes::Rectangle background(drawPos, size, Color::BLACK);
        background.draw();
        background.setColor(Color::WHITE);
        background.drawLines(border);

        // Draw selection box
        renderSelection(inputPos, field, console, rendered);

        // Draw the rendered text
        console.font.draw(text, inputPos, Console::FONT_HEIGHT, Color::WHITE);

        // Draw output
        if (!console.output.empty()) {
            console.font.draw(outputText, drawPos + Vector2f{border + padding, textSize.y + padding + lineSpacing},
                Console::FONT_HEIGHT, outputColor(console));
        }

        // Draw cursor
        if (field.getCursorType() != game::components::KeyboardInput::CursorType::NONE) {
            float lineOffset = static_cast<float>(Console::FONT_HEIGHT) + static_cast<float>(Console::FONT_HEIGHT) / 2;
            raylib::shapes::Rectangle cursor(
                inputPos + Vector2f{textbeforeCursorSize.x, lineOffset * static_cast<float>(field.cursorPos.y)},
                Vector2f{1, Console::FONT_HEIGHT}, Color::WHITE);

            cursor.draw();
        }
    }

} // namespace game::systems
