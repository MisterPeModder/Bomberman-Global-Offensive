/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** TestScene
*/

#include "game/scenes/TestScene.hpp"
#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Timer.hpp"
#include "game/Game.hpp"
#include "game/User.hpp"
#include "game/Users.hpp"
#include "game/components/Animation.hpp"
#include "game/components/Color.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Cube.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/Rectangle.hpp"
#include "game/components/Size.hpp"
#include "game/components/Textual.hpp"
#include "game/gui/components/Checkable.hpp"
#include "game/gui/components/Clickable.hpp"
#include "game/gui/components/Widget.hpp"
#include "game/systems/Animation.hpp"
#include "game/systems/Cube.hpp"
#include "game/systems/DrawText.hpp"
#include "game/systems/InputManager.hpp"
#include "game/systems/Model.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Audio.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/core/Sound.hpp"
#include "raylib/model/Animation.hpp"
#include "raylib/model/Model.hpp"
#include "util/util.hpp"

#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"

static raylib::model::Model &getTestingModel()
{
    static const std::filesystem::path testModelPath = util::makePath("assets", "models", "player", "raylibguy.iqm");
    static raylib::model::Model model(testModelPath);

    return model;
}

static raylib::model::Animation &getTestingAnimation()
{
    static const std::filesystem::path testAnimPath =
        std::filesystem::path("assets").append("animations").append("player").append("raylibguy_anim.iqm");
    static raylib::model::Animation anim(testAnimPath);

    return anim;
}

static void addTestWidgets(ecs::World &world)
{
    world.addEntity()
        .with<game::components::Position>(0.f, 0.f)
        .with<game::components::Textual>("I'm the ECS button", 20, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(
            0, game::gui::Widget::NullTag, 1, game::gui::Widget::NullTag, game::gui::Widget::NullTag, true)
        .with<game::gui::Clickable>(
            [](ecs::Entity _) {
                (void)_;
                Logger::logger.log(Logger::Severity::Debug, "On click event!");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::BLUE
                                                                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(0.f, 100.f)
        .with<game::components::Textual>("Hello ECS", 40, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1,
            [](ecs::Entity self, ecs::SystemData data, const game::Users::ActionEvent &event) {
                (void)self;
                (void)data;
                (void)event;
                Logger::logger.log(Logger::Severity::Debug, [&](std::ostream &writer) {
                    writer << "Text control! " << event.value << ", " << static_cast<size_t>(event.action);
                });
                return false;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(250.f, 0.f)
        .with<game::components::Textual>("I'm the ECS Checkbox!", 20, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(1, 0, game::gui::Widget::NullTag)
        .with<game::gui::Checkable>([&](ecs::Entity checkbox, bool checked) {
            world.getStorage<game::components::Textual>()[checkbox.getId()].color =
                (checked) ? raylib::core::Color::BLUE : raylib::core::Color::RED;
        })
        .build();

    world.addResource<game::Users>();
    world.addSystem<game::systems::DrawText>();
    world.addSystem<game::systems::InputManager>();
}

static void loadTestScene(ecs::World &world)
{
    world.addSystem<game::systems::DrawCube>();
    world.addEntity()
        .with<game::components::Cube>()
        .with<game::components::Position>(0.f, 0.f, 0.f)
        .with<game::components::Scale>(10)
        .with<game::components::Color>(raylib::core::Color::YELLOW)
        .build();

    raylib::core::Vector3 pos(0.f, -5.f, 0.f);
    raylib::core::Vector3 size(0.5f, 0.5f, 0.5f);
    raylib::core::Vector3 rotationAxis(1.f, 0.f, 0.f);
    float rotationAngle = -90;

    raylib::model::Model &testingModel = getTestingModel();
    raylib::model::Animation &testingAnimation = getTestingAnimation();

    world.addSystem<game::systems::DrawModel>();
    world.addSystem<game::systems::RunAnimation>();
    world.addEntity()
        .with<game::components::Model>(testingModel)
        .with<game::components::Position>(pos)
        .with<game::components::Size>(size)
        .with<game::components::RotationAngle>(rotationAngle)
        .with<game::components::RotationAxis>(rotationAxis)
        .with<game::components::Color>(raylib::core::Color::YELLOW)
        .with<game::components::Animation>(testingAnimation)
        .build();

    addTestWidgets(world);
}

namespace game
{
    TestScene::TestScene() { loadTestScene(_world); }
} // namespace game
