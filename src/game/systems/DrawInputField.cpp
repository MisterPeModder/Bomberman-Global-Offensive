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

#include "game/components/Position.hpp"
#include "game/gui/components/InputField.hpp"

#include "raylib/core/Color.hpp"
#include "raylib/text/text.hpp"

namespace game::systems
{
    void DrawInputField::run(ecs::SystemData data)
    {
        for (auto [pos, field] :
            ecs::join(data.getStorage<game::components::Position>(), data.getStorage<game::gui::InputField>())) {
            raylib::text::draw(field.contents, {pos.x, pos.y}, 10, raylib::core::Color::WHITE);
        }
    }

} // namespace game::systems
