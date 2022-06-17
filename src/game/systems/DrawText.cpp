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
            ::DrawText(text.text.c_str(), pos.x / 100 * raylib::core::Window::getWidth(),
                pos.y / 100 * raylib::core::Window::getHeight(), text.fontSize, text.color.asRaylib());
        }
    }
} // namespace game::systems
