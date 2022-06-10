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
#include "game/systems/Cube.hpp"
#include "raylib/core/Color.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/systems/Model.hpp"

namespace game
{
    void Worlds::loadGameWorld(ecs::World &world)
    {
        static const std::filesystem::path testModelPath =
            std::filesystem::path("assets").append("models").append("player").append("raylibguy.iqm");

        world.addSystem<game::systems::DrawRotatedModel>();

        world.addEntity()
            .with<game::Model>(testModelPath)
            .with<game::Position>(-5, -2, -5)
            .with<game::Size>(1, 0.5, 0.5)
            .with<game::RotationAngle>(-90)
            .with<game::RotationAxis>(1, 0, 0)
            .with<game::Color>(raylib::core::Color::PURPLE)
            .build();
        world.addEntity()
            .with<game::Model>(testModelPath)
            .with<game::Position>(-5, -2, 5)
            .with<game::Size>(1, 0.5, 0.5)
            .with<game::RotationAngle>(-90)
            .with<game::RotationAxis>(1, 0, 0)
            .with<game::Color>(raylib::core::Color::BROWN)
            .build();
        world.addEntity()
            .with<game::Model>(testModelPath)
            .with<game::Position>(5, -2, -5)
            .with<game::Size>(1, 0.5, 0.5)
            .with<game::RotationAngle>(-90)
            .with<game::RotationAxis>(1, 0, 0)
            .with<game::Color>(raylib::core::Color::DARK_GREEN)
            .build();
        world.addEntity()
            .with<game::Model>(testModelPath)
            .with<game::Position>(5, -2, 5)
            .with<game::Size>(1, 0.5, 0.5)
            .with<game::RotationAngle>(-90)
            .with<game::RotationAxis>(1, 0, 0)
            .with<game::Color>(raylib::core::Color::ORANGE)
            .build();
    }
} // namespace game
