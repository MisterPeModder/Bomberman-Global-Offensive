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
#include "ecs/resource/Timer.hpp"

#include "game/components/KeyboardInput.hpp"
#include "game/components/Position.hpp"
#include "game/components/Size2D.hpp"
#include "game/gui/components/Console.hpp"

#include "logger/Logger.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/core/Vector2.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/shapes/Rectangle.hpp"
#include "raylib/text/Font.hpp"

#include <cmath>
#include <string>

namespace game::systems
{
    void DrawConsole::run(ecs::SystemData data)
    {
        using Color = raylib::core::Color;
        using Vector2f = raylib::core::Vector2f;

        auto &timer = data.getResource<ecs::Timer>();
        double elapsed = timer.elapsed();

        auto &consoles = data.getStorage<game::gui::Console>();
        auto &positions = data.getStorage<game::components::Position>();
        auto &sizes = data.getStorage<game::components::Size2D>();
        auto &fields = data.getStorage<game::KeyboardInput>();

        for (auto [console, pos, size, field] : ecs::join(consoles, positions, sizes, fields)) {
            std::string text = ">>> " + field.contents;

            Vector2f drawPos{pos.x, pos.y};
            Vector2f textSize = console.font.measure(text, 20);
            Vector2f replySize = console.font.measure("- undefined", 20);

            float border = 2.0f;
            float padding = 10.0f;
            float lineSpacing = 5.0f;

            size.x = raylib::core::Window::getWidth();
            size.y = textSize.y + replySize.y + 2 * border + 2 * padding + lineSpacing;

            pos.x = 0;
            pos.y = raylib::core::Window::getHeight() - size.y;

            raylib::shapes::Rectangle background(drawPos, size, Color::BLACK);

            background.draw();
            background.setColor(Color::WHITE);
            background.drawLines(border);

            Vector2f inputPos{drawPos.x + border + padding, drawPos.y + padding};

            console.font.draw(text, inputPos, 20, Color::WHITE);
            console.font.draw("- undefined", drawPos + Vector2f{border + padding, textSize.y + padding + lineSpacing},
                20, Color::GRAY);

            console.timer = fmod(console.timer + elapsed, 1.0);

            Logger::logger.log(Logger::Severity::Information, [&](auto &out) { out << console.timer; });
            if (!field.focused || console.timer < 0.5)
                break;
            Logger::logger.log(Logger::Severity::Information, [&](auto &out) { out << "good"; });

            raylib::shapes::Rectangle cursor(inputPos + Vector2f{textSize.x, 0}, Vector2f{1, textSize.y}, Color::WHITE);

            cursor.draw();
        }
    }

} // namespace game::systems
