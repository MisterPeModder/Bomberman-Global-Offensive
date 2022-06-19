/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Draw FPS counter in debug mode
*/

#include "DrawFpsCounter.hpp"
#include "game/Engine.hpp"
#include "game/resources/Engine.hpp"
#include "raylib/core/Window.hpp"

namespace game::systems
{
    void DrawFpsCounter::run(ecs::SystemData data)
    {
        game::Engine *engine = data.getResource<game::resources::EngineResource>().engine;

        if (engine->getDebugMode())
            raylib::core::Window::drawFPS(10, 10);
    }

} // namespace game::systems
