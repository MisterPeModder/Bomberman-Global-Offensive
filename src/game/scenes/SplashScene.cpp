/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** SplashScene
*/

#include "SplashScene.hpp"

#include "util/util.hpp"

#include "game/components/Color.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Scale.hpp"
#include "game/components/Size.hpp"
#include "game/systems/Model.hpp"

static void loadSplashScene(ecs::World &world)
{
    static const std::filesystem::path testModelPath = util::makePath("assets", "models", "player", "raylibguy.iqm");

    world.addSystem<game::systems::DrawModel>();
    world.addStorage<game::components::Scale>();

    world.addEntity()
        .with<game::components::Model>(testModelPath)
        .with<game::components::Position>(-5.f, -2.f, -5.f)
        .with<game::components::Size>(1.f, 0.5f, 0.5f)
        .with<game::components::RotationAngle>(-90.f)
        .with<game::components::RotationAxis>(1.f, 0.f, 0.f)
        .with<game::components::Color>(raylib::core::Color::PURPLE)
        .build();
    world.addEntity()
        .with<game::components::Model>(testModelPath)
        .with<game::components::Position>(-5.f, -2.f, 5.f)
        .with<game::components::Size>(1.f, 0.5f, 0.5f)
        .with<game::components::RotationAngle>(-90.f)
        .with<game::components::RotationAxis>(1.f, 0.f, 0.f)
        .with<game::components::Color>(raylib::core::Color::BROWN)
        .build();
    world.addEntity()
        .with<game::components::Model>(testModelPath)
        .with<game::components::Position>(5.f, -2.f, -5.f)
        .with<game::components::Size>(1.f, 0.5f, 0.5f)
        .with<game::components::RotationAngle>(-90.f)
        .with<game::components::RotationAxis>(1.f, 0.f, 0.f)
        .with<game::components::Color>(raylib::core::Color::DARK_GREEN)
        .build();
    world.addEntity()
        .with<game::components::Model>(testModelPath)
        .with<game::components::Position>(5.f, -2.f, 5.f)
        .with<game::components::Size>(1.f, 0.5f, 0.5f)
        .with<game::components::RotationAngle>(-90.f)
        .with<game::components::RotationAxis>(1.f, 0.f, 0.f)
        .with<game::components::Color>(raylib::core::Color::ORANGE)
        .build();
}

namespace game
{
    SplashScene::SplashScene() { loadSplashScene(_world); }
} // namespace game
