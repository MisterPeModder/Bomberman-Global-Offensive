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
#include "raylib/core/Window.hpp"
#include "raylib/text/Font.hpp"

extern "C"
{
#include "raylib.h"
}

using namespace game::components;

namespace game::systems
{
    void DrawText::run(ecs::SystemData data)
    {
        for (auto [pos, text] :
            ecs::join(data.getStorage<game::components::Position>(), data.getStorage<game::components::Textual>())) {
            raylib::text::Font::getDefault().draw(text.text,
                {pos.x / 100.f * raylib::core::Window::getWidth(), pos.y / 100.f * raylib::core::Window::getHeight()},
                text.fontSize * raylib::core::Window::getHeight() / 720.f, text.color);
        }
    }
} // namespace game::systems
