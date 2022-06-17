/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** SplashScene
*/

#include "game/scenes/SplashScene.hpp"
#include "game/Engine.hpp"
#include "game/scenes/MainMenuScene.hpp"

#include "logger/Logger.hpp"
#include "util/util.hpp"

#include "raylib/core/Camera2D.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/scoped.hpp"

#include "game/components/Color.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/Scale.hpp"
#include "game/components/ScreenId.hpp"
#include "game/components/Textual.hpp"
#include "game/components/Texture2D.hpp"
#include "game/gui/components/Clickable.hpp"
#include "game/gui/components/Widget.hpp"

#include "game/resources/Engine.hpp"

#include "game/systems/DrawText.hpp"
#include "game/systems/DrawTexture.hpp"
#include "game/systems/InputManager.hpp"
#include "game/systems/SplashScreen.hpp"

#include "ecs/resource/Timer.hpp"

static void loadSplashScene(ecs::World &world)
{
    static const std::filesystem::path raylibLogoPath = util::makePath("assets", "raylib_logo.png");
    float scale = 3.f;

    world.addEntity()
        .with<game::components::Texture2D>(raylibLogoPath)
        .with<game::components::Position>((raylib::core::Window::getWidth() / 2) - ((128.f * scale) / 2),
            (raylib::core::Window::getHeight() / 2) - ((128.f * scale) / 2))
        .with<game::components::Scale>(scale)
        .with<game::components::RotationAngle>(0.f)
        .with<game::components::Color>(255, 255, 255, 0)
        .with<game::components::ScreenId>(0)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(0, game::gui::Widget::NullTag, game::gui::Widget::NullTag, game::gui::Widget::NullTag,
            game::gui::Widget::NullTag, true)
        .with<game::gui::Clickable>([&world](ecs::Entity) {
            world.getResource<game::resources::EngineResource>().engine->setScene<game::MainMenuScene>();
            Logger::logger.log(Logger::Severity::Debug, "Skip splash screen");
        })
        .build();
}

namespace game
{
    SplashScene::SplashScene()
    {
        _world.addResource<ecs::Timer>();
        _world.addResource<game::Users>();

        _world.addStorage<game::components::Textual>();

        _world.addSystem<game::systems::InputManager>();
        _world.addSystem<game::systems::SplashScreen>();
        _world.addSystem<game::systems::DrawTexture>();

        _globalNoDraw.add<game::systems::InputManager>();
        _globalNoDraw.add<game::systems::SplashScreen>();
        _global2D.add<game::systems::DrawTexture>();

        loadSplashScene(_world);
    }
} // namespace game
