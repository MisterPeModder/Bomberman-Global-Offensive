/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** AScene
*/

#include "game/scenes/AScene.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"

#include "game/Engine.hpp"
#include "game/resources/Engine.hpp"
#include "game/scenes/SettingsMenuScene.hpp"

namespace game
{
    AScene::AScene() {}

    AScene::~AScene() {}

    void AScene::setupWorld() {}

    void AScene::drawFrame()
    {
        _world.runSystems(_globalNoDraw);
        raylib::core::scoped::RenderTexture textureMode(
            _world.getResource<game::resources::EngineResource>().engine->getRenderTarget());
        raylib::core::Window::clear();
        {
            raylib::core::scoped::Mode3D mode3D(_defaultCamera3D);
            _world.runSystems(_global3D);
        };
        {
            raylib::core::scoped::Mode2D mode2D(_defaultCamera2D);
            _world.runSystems(_global2D);
        };
        _world.maintain();
    }

    ecs::World &AScene::getWorld() { return _world; }

    const ecs::World &AScene::getWorld() const { return _world; }
} // namespace game
