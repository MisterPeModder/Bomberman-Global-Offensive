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

extern "C"
{
#include "raylib.h"
}

namespace game
{
    void DrawText::run(ecs::SystemData data)
    {
        for (auto [pos, text] : ecs::join(data.getStorage<game::Position>(), data.getStorage<game::Textual>())) {
            ::DrawText(text.text.c_str(), pos.x, pos.y, text.fontSize, text.color.asRaylib());
        }
    }
} // namespace game
