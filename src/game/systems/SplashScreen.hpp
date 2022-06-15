/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** SplashScreen
*/

#ifndef GAME_SYSTEMS_SPLASHSCREEN_HPP_
#define GAME_SYSTEMS_SPLASHSCREEN_HPP_

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"

#include "ecs/resource/Resource.hpp"
#include "ecs/resource/Timer.hpp"

#include "game/Engine.hpp"
#include "game/scenes/SettingsMenuScene.hpp"

#include "game/resources/Engine.hpp"

#include "game/components/Color.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/ScreenId.hpp"
#include "game/components/Size.hpp"
#include "game/components/Textual.hpp"

static void buildRaylibSplash(ecs::SystemData &data)
{
    static const std::filesystem::path testModelPath = util::makePath("assets", "models", "player", "raylibguy.iqm");

    data.getResource<ecs::Entities>()
        .builder()
        .with<game::components::Model>(data.getStorage<game::components::Model>(), testModelPath)
        .with<game::components::Position>(data.getStorage<game::components::Position>(), 0.f, -2.f, 0.f)
        .with<game::components::Size>(data.getStorage<game::components::Size>(), 1.f, 0.5f, 0.5f)
        .with<game::components::RotationAngle>(data.getStorage<game::components::RotationAngle>(), -90.f)
        .with<game::components::RotationAxis>(data.getStorage<game::components::RotationAxis>(), 1.f, 0.f, 0.f)
        .with<game::components::Color>(data.getStorage<game::components::Color>(), raylib::core::Color::RAY_WHITE)
        .with<game::components::ScreenId>(data.getStorage<game::components::ScreenId>(), 0.f)
        .build();

    data.getResource<ecs::Entities>()
        .builder()
        .with<game::components::Textual>(
            data.getStorage<game::components::Textual>(), "RAYLIB", 72, raylib::core::Color::WHITE)
        .with<game::components::Position>(data.getStorage<game::components::Position>(), 400.f, 500.f)
        .build();
}

namespace game::systems
{
    struct SplashScreen : public ecs::System {
      public:
        void run(ecs::SystemData data) override final
        {
            auto &timer = data.getResource<ecs::Timer>();
            auto &entities = data.getResource<ecs::Entities>();

            if (timer.elapsed() >= 6)
                data.getResource<resources::EngineResource>().engine->setScene<game::SettingsMenuScene>();
            for (auto [screenId, entityId] : ecs::join(data.getStorage<components::ScreenId>(), entities)) {
                if (screenId.screenId < _screenId)
                    entities.kill(entityId);
                if (timer.elapsed() >= 3 && _screenId == 0) {
                    buildRaylibSplash(data);
                    _screenId = 1;
                }
            }
        }

      private:
        int _screenId;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_SPLASHSCREEN_HPP_ */
