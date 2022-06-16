/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** DrawText
*/

#include "DrawText.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "game/components/Position.hpp"
#include "game/components/Textual.hpp"
#include "raylib/text/text.hpp"

using namespace game::components;

namespace game::systems
{
    void DrawText::run(ecs::SystemData data)
    {
        for (auto [pos, text] :
            ecs::join(data.getStorage<game::components::Position>(), data.getStorage<game::components::Textual>())) {
            raylib::text::draw(text.text, {pos.x, pos.y}, text.fontSize, text.color);
        }
    }
} // namespace game::systems
