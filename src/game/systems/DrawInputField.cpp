/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Draw Input Fields
*/

#include "DrawInputField.hpp"

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"

#include "game/components/KeyboardInput.hpp"
#include "game/components/Position.hpp"

#include "logger/Logger.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/core/Vector2.hpp"
#include "raylib/shapes/Rectangle.hpp"
#include "raylib/text/Font.hpp"

namespace game::systems
{
    void DrawInputField::run(ecs::SystemData data)
    {
        using Color = raylib::core::Color;
        using Vector2f = raylib::core::Vector2f;

        auto &positions = data.getStorage<game::components::Position>();
        auto &fields = data.getStorage<game::KeyboardInput>();

        for (auto [pos, field] : ecs::join(positions, fields)) {
            Vector2f drawPos{pos.x, pos.y};
            Vector2f textSize = raylib::text::Font::getDefault().measure(field.contents, 15);
            Vector2f bgSize{textSize.x + 10, textSize.y + 10};

            raylib::shapes::Rectangle background(drawPos, bgSize, Color::BLACK);

            background.draw();
            background.setColor(Color::WHITE);
            background.drawLines(2);

            raylib::text::Font::getDefault().draw(field.contents, drawPos + Vector2f{5, 5}, 15, Color::WHITE);
        }
    }

} // namespace game::systems
