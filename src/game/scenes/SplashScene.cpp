/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** SplashScene
*/

#include "game/scenes/SplashScene.hpp"
#include "game/Engine.hpp"
#include "game/scenes/SettingsMenuScene.hpp"

#include "logger/Logger.hpp"
#include "util/util.hpp"

#include "raylib/core/Camera2D.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/scoped.hpp"

#include "game/components/Color.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Scale.hpp"
#include "game/components/ScreenId.hpp"
#include "game/components/Size.hpp"
#include "game/components/Textual.hpp"
#include "game/gui/components/Clickable.hpp"
#include "game/gui/components/Widget.hpp"

#include "game/resources/Engine.hpp"

#include "game/systems/DrawText.hpp"
#include "game/systems/InputManager.hpp"
#include "game/systems/Model.hpp"
#include "game/systems/SplashScreen.hpp"

#include "ecs/resource/Timer.hpp"

static void loadSplashScene(ecs::World &world)
{
    static const std::filesystem::path testModelPath = util::makePath("assets", "models", "player", "raylibguy.iqm");

    world.addEntity()
        .with<game::components::Model>(testModelPath)
        .with<game::components::Position>(0.f, -2.f, 0.f)
        .with<game::components::Size>(1.f, 0.5f, 0.5f)
        .with<game::components::RotationAngle>(-90.f)
        .with<game::components::RotationAxis>(1.f, 0.f, 0.f)
        .with<game::components::Color>(255, 255, 255, 0)
        .with<game::components::ScreenId>(0)
        .build();

    world.addEntity()
        .with<game::components::Position>(400.f, 500.f)
        .with<game::components::Textual>("VLAVe", 72, game::components::Color(255, 255, 255, 0))
        .with<game::components::ScreenId>(0)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(0, game::gui::Widget::NullTag, game::gui::Widget::NullTag, game::gui::Widget::NullTag,
            game::gui::Widget::NullTag, true)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->setScene<game::SettingsMenuScene>();
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

        _world.addStorage<game::components::Scale>();

        _world.addSystem<game::systems::InputManager>();
        _world.addSystem<game::systems::SplashScreen>();
        _world.addSystem<game::systems::DrawModel>();
        _world.addSystem<game::systems::DrawText>();

        _globalNoDraw.add<game::systems::InputManager>();
        _globalNoDraw.add<game::systems::SplashScreen>();
        _global3D.add<game::systems::DrawModel>();
        _global2D.add<game::systems::DrawText>();

        loadSplashScene(_world);
    }
} // namespace game
