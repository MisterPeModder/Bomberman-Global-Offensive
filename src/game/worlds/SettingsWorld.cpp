/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** SettingsWorld
*/

#include "SettingsWorld.hpp"

#include "util/util.hpp"

#include "game/components/Color.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Scale.hpp"
#include "game/components/Size.hpp"
#include "game/systems/Model.hpp"

static void loadSettingsWorld(ecs::World &world)
{
    static const std::filesystem::path testModelPath = util::makePath("assets", "models", "player", "raylibguy.iqm");

    world.addSystem<game::systems::DrawModel>();
    world.addStorage<game::components::Scale>();

    world.addEntity()
        .with<game::components::Model>(testModelPath)
        .with<game::components::Position>(0, -2, 0)
        .with<game::components::Size>(2.f, 0.5f, 0.5f)
        .with<game::components::RotationAngle>(-90)
        .with<game::components::RotationAxis>(1, 0, 0)
        .with<game::components::Color>(raylib::core::Color::BLUE)
        .build();
}

namespace game
{
    SettingsWorld::SettingsWorld() { loadSettingsWorld(_world); }
} // namespace game
