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
    void DrawConsole::run(ecs::SystemData data)
    {
        using Color = raylib::core::Color;
        using Vector2f = raylib::core::Vector2f;

        auto &consoles = data.getStorage<game::gui::Console>();
        auto &positions = data.getStorage<game::components::Position>();
        auto &sizes = data.getStorage<game::components::Size2D>();
        auto &fields = data.getStorage<game::KeyboardInput>();

        for (auto [console, pos, size, field] : ecs::join(consoles, positions, sizes, fields)) {
            std::string text = ">>> " + field.contents;
            std::string textBeforeCursor(text.cbegin(), text.cbegin() + 4 + field.cursorPos);

            Vector2f drawPos{pos.x, pos.y};
            Vector2f textSize = console.font.measure(text, 20);
            Vector2f textbeforeCursorSize = console.font.measure(textBeforeCursor, 20);
            Vector2f replySize = console.font.measure("- undefined", 20);

            float border = 2.0f;
            float padding = 10.0f;
            float lineSpacing = 5.0f;

            Vector2f inputPos{drawPos.x + border + padding, drawPos.y + padding};

            size.x = raylib::core::Window::getWidth();
            size.y = textSize.y + replySize.y + 2 * border + 2 * padding + lineSpacing;

            pos.x = 0;
            pos.y = raylib::core::Window::getHeight() - size.y;

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
            console.font.draw("- undefined", drawPos + Vector2f{border + padding, textSize.y + padding + lineSpacing},
                20, Color::GRAY);

            if (field.getCursorType() == game::KeyboardInput::CursorType::NONE)
                break;

            raylib::shapes::Rectangle cursor(
                inputPos + Vector2f{textbeforeCursorSize.x, 0}, Vector2f{1, textSize.y}, Color::WHITE);

            cursor.draw();
        }
    }

} // namespace game::systems
