/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Game
*/

#include "Game.hpp"
#include "game/AnimTimer.hpp"

#include "components/AiControlable.hpp"
#include "components/Animation.hpp"
#include "components/Bomb.hpp"
#include "components/BombNoClip.hpp"
#include "components/Collidable.hpp"
#include "components/Color.hpp"
#include "components/Controlable.hpp"
#include "components/Cube.hpp"
#include "components/CubeColor.hpp"
#include "components/Destructible.hpp"
#include "components/Explosion.hpp"
#include "components/GameEnded.hpp"
#include "components/History.hpp"
#include "components/Identity.hpp"
#include "components/KeybindIntercepter.hpp"
#include "components/KeyboardInput.hpp"
#include "components/Living.hpp"
#include "components/Model.hpp"
#include "components/Player.hpp"
#include "components/PlayerHud.hpp"
#include "components/Position.hpp"
#include "components/RotationAngle.hpp"
#include "components/RotationAxis.hpp"
#include "components/Scale.hpp"
#include "components/Size.hpp"
#include "components/Size2D.hpp"
#include "components/Smoke.hpp"
#include "components/Texture2D.hpp"
#include "components/Velocity.hpp"
#include "components/items/ItemIdentifier.hpp"

#include "ecs/Storage.hpp"
#include "ecs/resource/Timer.hpp"

#include "gui/components/Console.hpp"
#include "gui/components/Widget.hpp"
#include "logger/Logger.hpp"

#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/core/Vector2.hpp"
#include "raylib/core/Vector3.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/textures/Texture2D.hpp"

#include "resources/AssetMap.hpp"
#include "resources/Engine.hpp"
#include "resources/GameClock.hpp"
#include "resources/Map.hpp"
#include "resources/RandomDevice.hpp"

#include "systems/AiUpdate.hpp"
#include "systems/Animation.hpp"
#include "systems/Bomb.hpp"
#include "systems/CheckGameEnd.hpp"
#include "systems/Collision.hpp"
#include "systems/DrawConsole.hpp"
#include "systems/DrawFpsCounter.hpp"
#include "systems/DrawText.hpp"
#include "systems/DrawTexture.hpp"
#include "systems/DrawingCube.hpp"
#include "systems/Explosion.hpp"
#include "systems/InputManager.hpp"
#include "systems/Items.hpp"
#include "systems/Model.hpp"
#include "systems/Movement.hpp"
#include "systems/NoClip.hpp"
#include "systems/PlaySoundOnce.hpp"
#include "systems/Rectangle.hpp"
#include "systems/Smoke.hpp"
#include "systems/UpdateGameClock.hpp"
#include "systems/UpdateHud.hpp"
#include "systems/UpdateKeyboardInput.hpp"

#include "game/Engine.hpp"
#include "game/components/KeyboardInput.hpp"
#include "game/scenes/SettingsMenuScene.hpp"

#include "util/util.hpp"

#include "localization/Resources.hpp"

#include <cmath>

namespace game
{
    Game::Game(ecs::World &world, Parameters params) : _world(world), _map(params.mapSize), _params(params), _camera()
    {
    }

    const map::Map &Game::getMap() const { return _map; }

    raylib::core::Camera3D const &Game::getCamera() const { return this->_camera; }

    raylib::core::Camera3D &Game::getCamera() { return this->_camera; }

    void Game::setCamera(raylib::core::Camera3D &&camera) { this->_camera = std::move(camera); }

    void Game::_loadTextures()
    {
        auto &textures = _world.getResource<resources::Textures>();
        auto loadSkin = [](resources::Textures &texs, std::string_view msgid, std::string_view filename) {
            std::string msgidStr(msgid);
            std::string pathStr("assets/player/textures/");

            texs.emplace(msgidStr, pathStr + filename.data());
            texs.emplace("head_" + msgidStr, pathStr + "head_" + filename.data());
        };

        /// Map
        textures.emplace("crate", "assets/map/crate.png");
        textures.emplace("wall", "assets/map/wall.png");
        textures.emplace("ground", "assets/map/ground.png");
        /// Player
        loadSkin(textures, localization::resources::textures::rsTerroristOne.getMsgId(), "terrorist_1.png");
        loadSkin(textures, localization::resources::textures::rsTerroristTwo.getMsgId(), "terrorist_2.png");
        loadSkin(
            textures, localization::resources::textures::rsCounterTerroristOne.getMsgId(), "counter_terrorist_1.png");
        loadSkin(
            textures, localization::resources::textures::rsCounterTerroristTwo.getMsgId(), "counter_terrorist_2.png");
        loadSkin(textures, localization::resources::textures::rsNoSense.getMsgId(), "none_sense.png");
        loadSkin(textures, localization::resources::textures::rsRainbow.getMsgId(), "rainbow.png");
        textures.emplace(
            std::string(localization::resources::textures::rsUnknown.getMsgId()), "assets/player/textures/unknown.png");
        /// Activables
        textures.emplace("no_clip", "assets/items/activables/bonus_activable_no_clip.png");
        textures.emplace("mine", "assets/items/activables/bonus_activable_mine.png");
        textures.emplace("punch", "assets/items/activables/bonus_activable_punch.png");
        textures.emplace("kick_shoes", "assets/items/activables/bonus_activable_kick_shoes.png");
        textures.emplace("smoke", "assets/items/activables/bonus_activable_smoke.png");
        textures.emplace("stun", "assets/items/activables/bonus_activable_stunt.png");
        /// Power Ups
        textures.emplace("speed_up", "assets/items/power_ups/bonus_up_speed.png");
        textures.emplace("C4_up", "assets/items/power_ups/bonus_up_C4.png");
        textures.emplace("range_up", "assets/items/power_ups/bonus_up_range.png");
        /// Power Downs
        textures.emplace("speed_down", "assets/items/power_downs/bonus_down_speed.png");
        textures.emplace("C4_down", "assets/items/power_downs/bonus_down_C4.png");
        textures.emplace("range_down", "assets/items/power_downs/bonus_down_range.png");
        textures.emplace("control_down", "assets/items/power_downs/bonus_down_control.png");
        /// Weapons
        textures.emplace("C4", "assets/items/weapons/C4_Texture.png");
        textures.emplace("landmine", "assets/items/weapons/landmine_texture.png");
        textures.emplace("smoke_texture", "assets/items/weapons/smoke.png");
    }

    void Game::_loadMeshes()
    {
        auto &meshes = _world.getResource<resources::Meshes>();

        meshes.emplace("box", 1.f, 1.f, 1.f);
        meshes.emplace("ground", _map.getSize().x + 1.f, 0.0f, _map.getSize().y + 1.f);
        meshes.emplace("bonus", 0.5f, 10, 10);
        meshes.emplace("activable", 1.f, 0.f, 1.f);
        meshes.emplace("smoke_sphere", 2.f, 10, 10);
    }

    void Game::_loadModels()
    {
        auto &textures = _world.getResource<resources::Textures>();
        auto &meshes = _world.getResource<resources::Meshes>();
        auto &models = _world.getResource<resources::Models>();

        /////// Map
        models.emplace("ground", meshes.get("ground"), false).setMaterialMapTexture(textures.get("ground"));
        models.emplace("crate", meshes.get("box"), false).setMaterialMapTexture(textures.get("crate"));
        models.emplace("wall", meshes.get("box"), false).setMaterialMapTexture(textures.get("wall"));
        models.emplace("C4", "assets/items/weapons/c4.iqm").setMaterialMapTexture(textures.get("C4"));
        models.emplace("landmine", "assets/items/weapons/landmine.iqm").setMaterialMapTexture(textures.get("landmine"));
        models.emplace("smoke_sphere", meshes.get("smoke_sphere"), false)
            .setMaterialMapTexture(textures.get("smoke_texture"));
        ////// Items
        auto &bonusMesh = meshes.get("bonus");
        /// Power Ups
        models.emplace("speed_up", bonusMesh, false).setMaterialMapTexture(textures.get("speed_up"));
        models.emplace("C4_up", bonusMesh, false).setMaterialMapTexture(textures.get("C4_up"));
        models.emplace("range_up", bonusMesh, false).setMaterialMapTexture(textures.get("range_up"));
        /// Power Downs
        models.emplace("speed_down", bonusMesh, false).setMaterialMapTexture(textures.get("speed_down"));
        models.emplace("C4_down", bonusMesh, false).setMaterialMapTexture(textures.get("C4_down"));
        models.emplace("range_down", bonusMesh, false).setMaterialMapTexture(textures.get("range_down"));
        models.emplace("control_down", bonusMesh, false).setMaterialMapTexture(textures.get("control_down"));
        /// Activables
        auto &activable = meshes.get("activable");
        models.emplace("no_clip", activable, false).setMaterialMapTexture(textures.get("no_clip"));
        models.emplace("mine", activable, false).setMaterialMapTexture(textures.get("mine"));
        models.emplace("kick_shoes", activable, false).setMaterialMapTexture(textures.get("kick_shoes"));
        models.emplace("smoke", activable, false).setMaterialMapTexture(textures.get("smoke"));
        models.emplace("stun", activable, false).setMaterialMapTexture(textures.get("stun"));
        models.emplace("punch", activable, false).setMaterialMapTexture(textures.get("punch"));
    }

    void Game::_loadSounds()
    {
        auto &sounds = _world.getResource<resources::Sounds>();

        sounds.emplace("C4", "assets/audio/sounds/c4_explosion.ogg");
        sounds.emplace("stun", "assets/audio/sounds/flashbang.ogg");
        sounds.emplace("smoke", "assets/audio/sounds/smoke.ogg");
        sounds.emplace("victory", "assets/audio/sounds/wins.ogg");
    }

    void Game::setup()
    {
        size_t width = _map.getSize().x;
        size_t depth = _map.getSize().y;

        _camera.setPosition(
            {width / 2.f, 18.f /*static_cast<float>(width)*/, static_cast<float>(depth)}); // Camera position
        _camera.setTarget({width / 2.f, 0.f, depth / 2.f});                                // Camera looking at point
        _camera.setUp({0.0f, 1.0f, 0.0f}); // Camera up vector (rotation towards target)
        _camera.setFovY(50.0f);            // Camera field-of-view Y
        _camera.setProjection(CAMERA_PERSPECTIVE);

        _world.addSystem<game::systems::UpdateKeyboardInput>();

        /// FPS Counter
        _world.addSystem<game::systems::DrawFpsCounter>();
        /// Console
        _world.addSystem<game::systems::DrawConsole>();

        _world.addEntity().with<game::components::GameEnded>().build();

        _world.addEntity()
            .with<game::gui::Console>()
            .with<game::components::History>()
            .with<game::components::Position>(0.f, 50.f, 0.f)
            .with<game::components::Size2D>(720, 20)
            .with<game::components::KeyboardInput>(&game::gui::Console::runCommand)
            .with<game::components::Controlable>(game::User::UserId::User1, &game::gui::Console::handleInput)
            .build();

        /// Add world resources
        _world.addResource<ecs::Timer>();
        _world.addResource<game::AnimTimer>();
        _world.addResource<resources::Map>(_map);
        _world.addResource<resources::Textures>();
        _world.addResource<resources::Meshes>();
        _world.addResource<resources::Models>();
        _world.addResource<resources::Sounds>();
        _world.addResource<resources::RandomDevice>();
        _world.addResource<resources::GameClock>();
        /// Add world storages
        _world.addStorage<components::Bomb>();
        _world.addStorage<components::ItemIdentifier>();
        _world.addStorage<game::gui::Widget>();
        _world.addStorage<components::KeyboardInput>();
        _world.addStorage<components::Smoke>();
        _world.addStorage<components::RotationAngle>();
        _world.addStorage<components::RotationAxis>();
        _world.addStorage<components::Model>();
        _world.addStorage<components::CubeColor>();
        _world.addStorage<components::Cube>();
        _world.addStorage<components::KeybindIntercepter>();
        _world.addStorage<components::SoundReference>();
        _world.addStorage<components::GameEnded>();
        _world.addStorage<components::Explosion>();
        _world.addStorage<components::PlayerHud>();
        /// Add world systems
        _world.addSystem<systems::AiUpdate>();
        _world.addSystem<systems::DrawModel>();
        _world.addSystem<systems::RunAnimation>();
        _world.addSystem<systems::InputManager>();
        _world.addSystem<systems::Movement>();
        _world.addSystem<systems::Collision>();
        _world.addSystem<systems::ExplodeBomb>();
        _world.addSystem<systems::PickupItem>();
        _world.addSystem<systems::DisableBombNoClip>();
        _world.addSystem<systems::UpdateItemTimer>();
        _world.addSystem<systems::MoveSmoke>();
        _world.addSystem<systems::PlaySoundReferences>();
        _world.addSystem<systems::DisableNoClip>();
        _world.addSystem<systems::CheckGameEnd>();
        _world.addSystem<systems::ClearExplosions>();
        _world.addSystem<systems::UpdateGameClock>();
        _world.addSystem<systems::DrawFlippedTexture>();
        _world.addSystem<systems::DrawRectangle>();
        _world.addSystem<systems::DrawText>();
        _world.addSystem<systems::UpdateHud>();
        /// Setup world systems tags
        _handleInputs.add<systems::InputManager>();
        _update.add<systems::AiUpdate, systems::Movement, systems::ExplodeBomb, systems::PickupItem,
            systems::DisableBombNoClip, systems::UpdateItemTimer, systems::RunAnimation, systems::MoveSmoke,
            systems::CheckGameEnd, systems::PlaySoundReferences, systems::DisableNoClip, systems::ClearExplosions,
            systems::UpdateHud>();
        _resolveCollisions.add<systems::Collision, systems::UpdateGameClock>();
        _drawing.add<systems::DrawModel>();
        _drawing2d.add<systems::DrawRectangle, systems::DrawFlippedTexture, systems::DrawText,
            game::systems::DrawConsole, game::systems::DrawFpsCounter>();

        _loadTextures();
        _loadMeshes();
        _loadModels();
        _loadSounds();

        /// Player
        auto &textures = _world.getResource<resources::Textures>();

        for (size_t i = 0; i < _params.playerCount; i++) {
            User::UserId owner = static_cast<User::UserId>(i);
            raylib::core::Vector2u cell = _map.getPlayerStartingPosition(owner);

            auto playerEntity =
                _world.addEntity()
                    .with<components::Position>(static_cast<float>(cell.x), 0.f, static_cast<float>(cell.y))
                    .with<components::Velocity>()
                    .with<components::Living>(_params.livesCount)
                    .with<components::Collidable>()
                    .with<components::Player>()
                    .with<components::Size>(0.5f, 0.5f, 0.5f)
                    .with<components::Model>(util::makePath("assets", "player", "player.iqm"))
                    .with<components::Animation>(util::makePath("assets", "player", "player.iqm"))
                    .with<components::Color>(raylib::core::Color::WHITE)
                    .with<components::RotationAngle>(0.0f)
                    .with<components::RotationAxis>(0.f, 1.f, 0.f)
                    .with<components::Controlable>(owner, components::Player::handleActionEvent)
                    .with<components::AiControlable>()
                    .with<components::BombNoClip>()
                    .with<components::Identity>()
                    .build();
            _world.getStorage<components::Model>()[playerEntity.getId()].setMaterialMapTexture(
                textures.get(_params.skinList.front()));
            components::PlayerHud::createHud(owner, textures.get("head_" + _params.skinList.front()), _world);
            _params.skinList.pop();
        }

        /// Ground
        _world.addEntity()
            .with<components::Position>(width / 2.f - 0.5f, 0.f, depth / 2.f - 0.5f)
            .with<game::components::Scale>(3.f)
            .with<game::components::Color>(raylib::core::Color::WHITE)
            .with<game::components::ModelReference>(_world.getResource<resources::Models>().get("ground"))
            .build();

        /// Walls, crates
        for (float z = -1; static_cast<float>(z) < depth + 1; z++) {
            for (float x = -1; static_cast<float>(x) < width + 1; x++) {
                bool wall = false;
                bool destructible = false;
                raylib::core::Color color = raylib::core::Color(40, 40, 40);

                if (z == -1 || x == -1 || z == depth || x == width)
                    wall = true;
                else {
                    switch (_map.getElement({static_cast<unsigned int>(x), static_cast<unsigned int>(z)})) {
                        case map::Map::Element::Crate:
                            wall = true;
                            destructible = true;
                            color = raylib::core::Color(110, 85, 70);
                            break;
                        case map::Map::Element::Wall: wall = true; break;
                        default: break;
                    }
                }
                if (wall) {
                    auto builder = _world.addEntity();

                    (void)builder.with<components::Position>(x, 0.5f, z)
                        .with<components::Collidable>()
                        .with<components::Wall>()
                        .with<game::components::Scale>(1.f)
                        .with<components::Size>(1.f, 1.f, 1.f);
                    if (destructible) {
                        (void)builder.with<components::Destructible>()
                            .with<game::components::Color>(raylib::core::Color::WHITE)
                            .with<game::components::ModelReference>(
                                _world.getResource<resources::Models>().get("crate"));
                    } else {
                        (void)builder.with<game::components::Color>(raylib::core::Color::WHITE)
                            .with<game::components::ModelReference>(
                                _world.getResource<resources::Models>().get("wall"));
                    }
                    builder.build();
                }
            }
        }
    }

    void Game::drawFrame()
    {
        _world.getResource<game::resources::EngineResource>().engine->updateMusicStreams();
        _camera.update();

        _world.runSystem<game::systems::UpdateKeyboardInput>();
        _world.getResource<ecs::Timer>().reset();

        _world.runSystems(_handleInputs);
        _world.runSystems(_update);
        _world.runSystems(_resolveCollisions);

        raylib::core::scoped::RenderTexture textureMode(
            _world.getResource<game::resources::EngineResource>().engine->getRenderTarget());
        raylib::core::Window::clear();
        {
            raylib::core::scoped::Mode3D mode3D(_camera);
            _world.runSystems(_drawing);
        };
        {
            raylib::core::scoped::Mode2D mode2D((raylib::core::Camera2D()));
            _world.runSystems(_drawing2d);
        };
        _world.maintain();
    }
} // namespace game
