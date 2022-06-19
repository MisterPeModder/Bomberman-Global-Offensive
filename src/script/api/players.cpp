/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** JS Player Object Methods
*/

/// @file
/// @internal
///
/// See api.js for documentation.

#include "ecs/Storage.hpp"
#include "ecs/World.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Entities.hpp"

#include "game/Engine.hpp"
#include "game/Game.hpp"
#include "game/components/AiControlable.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Player.hpp"
#include "game/components/Position.hpp"
#include "game/scenes/GameScene.hpp"

#include "script/Engine.hpp"
#include "script/JsException.hpp"
#include "script/script.hpp"

#include <optional>

namespace bmjs::players
{
    template <typename T>
    static std::optional<T> withPlayer(
        bmjs::Number playerId, std::shared_ptr<bmjs::Engine> &engine, std::function<T(ecs::Entity, ecs::World &)> func)
    {
        int intId = static_cast<int>(playerId);

        if (!engine || intId < 0 || intId >= static_cast<int>(game::User::UserId::UserCount))
            return {};
        auto id = static_cast<game::User::UserId>(intId);

        auto &world = engine->getGameEngine().getScene().getWorld();
        auto &players = world.getStorage<game::components::Player>();
        auto &controlables = world.getStorage<game::components::Controlable>();
        auto &entities = world.getResource<ecs::Entities>();

        auto join = ecs::join(players, controlables, entities);

        auto found = std::find_if(join.begin(), join.end(), [id](auto i) { return std::get<1>(i).userId == id; });

        if (found == join.end())
            return {};
        return func(std::get<2>(*found), world);
    }
} // namespace bmjs::players

BMJS_API_START(players)

BMJS_DEFINE bmjs::Number players_exists(bmjs::Number playerId)
{
    auto engine = bmjs::Engine::instance().lock();

    auto result = bmjs::players::withPlayer<bool>(playerId, engine, [](ecs::Entity, ecs::World &) { return true; });
    return !!(result && *result);
}

BMJS_DEFINE bmjs::Number players_getX(bmjs::Number playerId)
{
    auto engine = bmjs::Engine::instance().lock();

    auto result = bmjs::players::withPlayer<bmjs::Number>(playerId, engine, [](ecs::Entity self, ecs::World &world) {
        return world.getStorage<game::components::Position>()[self.getId()].x;
    });
    if (!result)
        return -1;
    return *result;
}

BMJS_DEFINE bmjs::Number players_getY(bmjs::Number playerId)
{
    auto engine = bmjs::Engine::instance().lock();

    auto result = bmjs::players::withPlayer<bmjs::Number>(playerId, engine, [](ecs::Entity self, ecs::World &world) {
        return world.getStorage<game::components::Position>()[self.getId()].z;
    });
    if (!result)
        return -1;
    return *result;
}

BMJS_DEFINE void players_setX(bmjs::Number playerId, bmjs::Number x)
{
    auto engine = bmjs::Engine::instance().lock();

    bmjs::players::withPlayer<int>(playerId, engine, [x](ecs::Entity self, ecs::World &world) {
        world.getStorage<game::components::Position>()[self.getId()].x = x;
        return 0;
    });
}

BMJS_DEFINE void players_setY(bmjs::Number playerId, bmjs::Number y)
{
    auto engine = bmjs::Engine::instance().lock();

    bmjs::players::withPlayer<int>(playerId, engine, [y](ecs::Entity self, ecs::World &world) {
        world.getStorage<game::components::Position>()[self.getId()].z = y;
        return 0;
    });
}

BMJS_DEFINE void players_setPos(bmjs::Number playerId, bmjs::Number x, bmjs::Number y)
{
    auto engine = bmjs::Engine::instance().lock();

    bmjs::players::withPlayer<int>(playerId, engine, [x, y](ecs::Entity self, ecs::World &world) {
        auto &pos = world.getStorage<game::components::Position>()[self.getId()];
        pos.x = x;
        pos.z = y;
        return 0;
    });
}

BMJS_DEFINE void players_moveTo(bmjs::Number playerId, bmjs::Number x, bmjs::Number y)
{
    auto engine = bmjs::Engine::instance().lock();

    bmjs::players::withPlayer<int>(playerId, engine, [x, y](ecs::Entity self, ecs::World &world) {
        auto &ai = world.getStorage<game::components::AiControlable>()[self.getId()];

        ai.pathFind({static_cast<float>(x), static_cast<float>(y)}, self, ecs::SystemData(world));
        return 0;
    });
}

BMJS_DEFINE void players_stop(bmjs::Number playerId)
{
    auto engine = bmjs::Engine::instance().lock();

    bmjs::players::withPlayer<int>(playerId, engine, [](ecs::Entity self, ecs::World &world) {
        auto &ai = world.getStorage<game::components::AiControlable>()[self.getId()];

        ai.path.clear();
        game::components::Player::move(self, ecs::SystemData(world), game::GameAction::MOVE_RIGHT, 0.0);
        return 0;
    });
}

BMJS_API_END
