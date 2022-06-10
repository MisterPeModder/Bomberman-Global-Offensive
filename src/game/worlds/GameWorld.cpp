/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** GameWorld
*/

#include "Worlds.hpp"
#include "ecs/Storage.hpp"
#include "game/components/Cube.hpp"
#include "game/components/Rectangle.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/systems/Cube.hpp"
#include "game/systems/Model.hpp"
#include "raylib/core/Color.hpp"
#include "util/util.hpp"

namespace game
{
    void Worlds::loadGameWorld(ecs::World &world)
    {
        static const std::filesystem::path testModelPath =
            util::makePath("assets", "models", "player", "raylibguy.iqm");

        world.addSystem<game::systems::DrawRotatedModel>();

        world.addEntity()
            .with<game::components::Model>(testModelPath)
            .with<game::components::Position>(-5, -2, -5)
            .with<game::components::Size>(1.f, 0.5f, 0.5f)
            .with<game::components::RotationAngle>(-90.f)
            .with<game::components::RotationAxis>(1, 0, 0)
            .with<game::components::Color>(raylib::core::Color::PURPLE)
            .build();
        world.addEntity()
            .with<game::components::Model>(testModelPath)
            .with<game::components::Position>(-5, -2, 5)
            .with<game::components::Size>(1.f, 0.5f, 0.5f)
            .with<game::components::RotationAngle>(-90.f)
            .with<game::components::RotationAxis>(1, 0, 0)
            .with<game::components::Color>(raylib::core::Color::BROWN)
            .build();
        world.addEntity()
            .with<game::components::Model>(testModelPath)
            .with<game::components::Position>(5, -2, -5)
            .with<game::components::Size>(1.f, 0.5f, 0.5f)
            .with<game::components::RotationAngle>(-90)
            .with<game::components::RotationAxis>(1, 0, 0)
            .with<game::components::Color>(raylib::core::Color::DARK_GREEN)
            .build();
        world.addEntity()
            .with<game::components::Model>(testModelPath)
            .with<game::components::Position>(5, -2, 5)
            .with<game::components::Size>(1.f, 0.5f, 0.5f)
            .with<game::components::RotationAngle>(-90)
            .with<game::components::RotationAxis>(1, 0, 0)
            .with<game::components::Color>(raylib::core::Color::ORANGE)
            .build();
    }
} // namespace game
