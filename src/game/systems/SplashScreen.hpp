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

#include "logger/Logger.hpp"

#include "ecs/resource/Resource.hpp"
#include "ecs/resource/Timer.hpp"

#include "raylib/core/Color.hpp"

#include "game/Engine.hpp"
#include "game/scenes/MainMenuScene.hpp"

#include "game/resources/Engine.hpp"

#include "game/components/Color.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/ScreenId.hpp"
#include "game/components/Sound.hpp"
#include "game/components/Texture2D.hpp"
#include "game/components/UseCheck.hpp"
#include "game/gui/components/Clickable.hpp"
#include "game/gui/components/Widget.hpp"

#include "game/systems/InputManager.hpp"

static void buildStudioSplash(ecs::SystemData &data)
{
    static const std::filesystem::path studioLogoPath = util::makePath("assets", "studio_logo.png");
    float scale = 1.f;
    static const std::filesystem::path studioSoundPath =
        util::makePath("assets", "audio", "sounds", "vlave_splash.ogg");

    data.getResource<ecs::Entities>()
        .builder()
        .with<game::components::ScreenId>(data.getStorage<game::components::ScreenId>(), 1)
        .with<game::components::Sound>(data.getStorage<game::components::Sound>(), studioSoundPath)
        .with<game::components::UseCheck>(data.getStorage<game::components::UseCheck>())
        .build();

    data.getResource<ecs::Entities>()
        .builder()
        .with<game::components::ScreenId>(data.getStorage<game::components::ScreenId>(), 1)
        .with<game::components::Texture2D>(data.getStorage<game::components::Texture2D>(), studioLogoPath)
        .with<game::components::Position>(data.getStorage<game::components::Position>(),
            ((raylib::core::Window::getWidth() / 2) - ((400.f * scale) / 2)) / (raylib::core::Window::getWidth() / 100),
            ((raylib::core::Window::getHeight() / 2) - ((200.f * scale) / 2))
                / (raylib::core::Window::getHeight() / 100))
        .with<game::components::Scale>(data.getStorage<game::components::Scale>(), scale)
        .with<game::components::RotationAngle>(data.getStorage<game::components::RotationAngle>(), 0.f)
        .with<game::components::Color>(
            data.getStorage<game::components::Color>(), raylib::core::Color(255, 255, 255, 0))
        .with<game::components::Controlable>(
            data.getStorage<game::components::Controlable>(), game::User::UserId::User1)
        .with<game::gui::Widget>(data.getStorage<game::gui::Widget>(), 0, game::gui::Widget::NullTag,
            game::gui::Widget::NullTag, game::gui::Widget::NullTag, game::gui::Widget::NullTag, true)
        .with<game::gui::Clickable>(data.getStorage<game::gui::Clickable>(),
            [](ecs::Entity) {
                Logger::logger.log(Logger::Severity::Debug, "Tried to skip splash screen but it's disabled for now");
            })
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
            int colorMoveValue = 5;

            if (timer.elapsed() >= 6) {
                data.getResource<resources::EngineResource>().engine->setScene<game::MainMenuScene>();
                data.getResource<resources::EngineResource>().engine->setCurrentMusic(
                    game::Engine::PreloadedMusics::MAIN_MENU_THEME);
            }
            for (auto [color] : ecs::join(data.getStorage<components::Color>())) {
                if (_screenId == 0) {
                    if (timer.elapsed() < 1.5) {
                        if (color.a <= 255 - colorMoveValue)
                            color.a += colorMoveValue;
                    } else if (color.a >= 0 + colorMoveValue)
                        color.a -= colorMoveValue;
                } else if (_screenId == 1) {
                    if (timer.elapsed() < 4.5) {
                        if (color.a <= 255 - colorMoveValue)
                            color.a += colorMoveValue;
                    } else if (color.a >= 0 + colorMoveValue)
                        color.a -= colorMoveValue;
                }
            }
            for (auto [text] : ecs::join(data.getStorage<components::Textual>())) {
                if (_screenId == 0) {
                    if (timer.elapsed() < 1.5) {
                        if (text.color.a <= 255 - colorMoveValue)
                            text.color.a += colorMoveValue;
                    } else if (text.color.a >= 0 + colorMoveValue)
                        text.color.a -= colorMoveValue;
                } else if (_screenId == 1) {
                    if (timer.elapsed() < 4.5) {
                        if (text.color.a <= 255 - colorMoveValue)
                            text.color.a += colorMoveValue;
                    } else if (text.color.a >= 0 + colorMoveValue)
                        text.color.a -= colorMoveValue;
                }
            }
            for (auto [screenId, sound] :
                ecs::join(data.getStorage<components::ScreenId>(), data.getStorage<components::Sound>())) {
                if (screenId.screenId < _screenId)
                    sound.stop();
            }
            for (auto [screenId, entityId] : ecs::join(data.getStorage<components::ScreenId>(), entities)) {
                if (screenId.screenId < _screenId)
                    entities.kill(entityId);
                if (timer.elapsed() >= 3 && _screenId == 0) {
                    buildStudioSplash(data);
                    _screenId = 1;
                }
            }
        }

      private:
        int _screenId;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_SPLASHSCREEN_HPP_ */
