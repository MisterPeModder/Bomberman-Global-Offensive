/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** DrawHud
*/

#include "systems/DrawHud.hpp"
#include "raylib/core/Window.hpp"
#include "systems/DrawText.hpp"
#include "logger/Logger.hpp"

extern "C"
{
#include "raylib.h"
}

namespace game::systems
{
    void DrawHud::drawDataHud(int x, int y, std::string text, raylib::core::Color color)
    {
        ::DrawText(text.c_str(), x / 100 * raylib::core::Window::getWidth(),
            y / 100 * raylib::core::Window::getHeight(), 20, color.asRaylib());
    }
    void DrawHud::run(ecs::SystemData data)
    {
        Logger::logger.log(Logger::Severity::Information, "enter in hud draw");
        for (auto [hud] : ecs::join(data.getStorage<game::components::Hud>())) {
            //game::components::Textual nbbom(std::to_string(hud.nbBomb), 20, raylib::core::Color::WHITE);
            drawDataHud(10, 10, std::to_string(hud.nbBomb), raylib::core::Color::BLUE);
        }
    }
} // namespace game::systems
