/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** SplashWorld
*/

#include "ecs/Storage.hpp"
#include "game/Game.hpp"
#include "game/User.hpp"
#include "game/Users.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Cube.hpp"
#include "game/components/Textual.hpp"
#include "game/systems/Cube.hpp"
#include "game/systems/DrawText.hpp"
#include "game/systems/Model.hpp"
#include "game/worlds/Worlds.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Color.hpp"
#include "util/util.hpp"

namespace game
{
    void Worlds::loadSplashWorld(ecs::World &world)
    {
        static const std::filesystem::path testModelPath =
            util::makePath("assets", "models", "player", "raylibguy.iqm");

        world.addSystem<game::systems::DrawModel>();

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
} // namespace game
