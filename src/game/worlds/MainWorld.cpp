/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** TestWorld
*/

#include "Worlds.hpp"
#include "ecs/Storage.hpp"
#include "game/User.hpp"
#include "game/Users.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Cube.hpp"
#include "game/components/Textual.hpp"
#include "game/systems/Cube.hpp"
#include "game/systems/DrawText.hpp"
#include "game/systems/Model.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Color.hpp"

namespace game
{
    void Worlds::loadMainWorld(ecs::World &world)
    {
        static const std::filesystem::path testModelPath =
            std::filesystem::path("assets").append("models").append("player").append("raylibguy.iqm");

        world.addSystem<game::systems::DrawRotatedModel>();

        world.addEntity()
            .with<game::Model>(testModelPath)
            .with<game::Position>(0, -2, 0)
            .with<game::Size>(0.5, 0.5, 0.5)
            .with<game::RotationAngle>(-90)
            .with<game::RotationAxis>(1, 0, 0)
            .with<game::Color>(raylib::core::Color::GREEN)
            .build();
    }
} // namespace game
