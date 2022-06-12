/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** MainWorld
*/

#include "MainWorld.hpp"

MainWorld::MainWorld(ecs::World &_world)
{
    static const std::filesystem::path testModelPath =
        util::makePath("assets", "models", "player", "raylibguy.iqm");

    _world.addSystem<game::systems::DrawModel>();

    _world.addEntity()
        .with<game::components::Model>(testModelPath)
        .with<game::components::Position>(0, -2, 0)
        .with<game::components::Size>(0.5f, 0.5f, 0.5f)
        .with<game::components::RotationAngle>(-90)
        .with<game::components::RotationAxis>(1, 0, 0)
        .with<game::components::Color>(raylib::core::Color::GREEN)
        .build();
}
