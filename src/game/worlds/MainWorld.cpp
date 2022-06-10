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
#include "util/util.hpp"

namespace game
{
    void Worlds::loadMainWorld(ecs::World &world)
    {
        static const std::filesystem::path testModelPath =
            util::makePath("assets", "models", "player", "raylibguy.iqm");

        world.addSystem<game::systems::DrawRotatedModel>();

        world.addEntity()
            .with<game::components::Model>(testModelPath)
            .with<game::components::Position>(0, -2, 0)
            .with<game::components::Size>(0.5f, 0.5f, 0.5f)
            .with<game::components::RotationAngle>(-90)
            .with<game::components::RotationAxis>(1, 0, 0)
            .with<game::components::Color>(raylib::core::Color::GREEN)
            .build();
    }
} // namespace game
