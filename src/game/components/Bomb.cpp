/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Bomb
*/

#include "Bomb.hpp"
#include <cmath>
#include "BombNoClip.hpp"
#include "Collidable.hpp"
#include "Color.hpp"
#include "Destructible.hpp"
#include "Identity.hpp"
#include "Living.hpp"
#include "Model.hpp"
#include "Player.hpp"
#include "RotationAngle.hpp"
#include "RotationAxis.hpp"
#include "Size.hpp"
#include "Velocity.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "game/Game.hpp"
#include "game/resources/AssetMap.hpp"
#include "game/resources/Map.hpp"
#include "items/Item.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Vector2.hpp"

namespace game::components
{
    void Bomb::explode(const Position &bombPos, ecs::SystemData data, ecs::Entity self)
    {
        /// Need to keep this check to avoid infinity loop with chained explosions
        if (this->exploded)
            return;
        this->exploded = true;
        if (type == Type::Classic) {
            for (auto [id, player] : ecs::join(data.getStorage<Identity>(), data.getStorage<Player>())) {
                if (id.id == owner)
                    --player.placedBombs;
            }
        }
        /// Retrieve storages
        auto &positions = data.getStorage<Position>();
        auto &sizes = data.getStorage<Size>();
        auto maybeDestructible = ecs::maybe(data.getStorage<Destructible>());
        auto maybeLiving = ecs::maybe(data.getStorage<Living>());
        auto maybeBomb = ecs::maybe(data.getStorage<Bomb>());
        auto &entities = data.getResource<ecs::Entities>();

        entities.kill(self);
        /// Retrieve exploded cells
        game::map::Map &map = data.getResource<game::resources::Map>().map;
        std::vector<raylib::core::Vector2u> explodedPositions;

        map.fillExplodedPositions(explodedPositions,
            raylib::core::Vector2u(static_cast<unsigned int>(bombPos.x), static_cast<unsigned int>(bombPos.z)),
            this->radius);
        if (explodedPositions.empty())
            return;

        /// Test for destructible and living entities if they are in an exploded cell.
        for (auto [pos, size, destructible, living, bomb, id] :
            ecs::join(positions, sizes, maybeDestructible, maybeLiving, maybeBomb, entities)) {
            /// Do not care about dead entities
            if ((!destructible && !living && !bomb) || (living && living->hp == 0))
                continue;

            raylib::core::Vector2u roundedPos2D = game::Game::worldPosToMapCell(pos);

            if (std::find(explodedPositions.begin(), explodedPositions.end(), roundedPos2D) == explodedPositions.end()
                && (!living || !explodeLiving(pos, size, roundedPos2D, explodedPositions)))
                continue;

            if (living) {
                Logger::logger.log(Logger::Severity::Debug, "Living entity hit by a bomb"); // living->hp--;
            }
            if (destructible) {
                entities.kill(id);
                auto &elem = map.getElement(roundedPos2D);
                if (elem == game::map::Map::Element::Crate)
                    Item::spawnRandomItem(data, roundedPos2D);
                elem = game::map::Map::Element::Empty;
            }
            if (bomb)
                bomb->explode(pos, data, id);
        }
    }

    bool Bomb::explodeLiving(raylib::core::Vector3f pos, raylib::core::Vector3f size,
        raylib::core::Vector2u roundedPos2D, const std::vector<raylib::core::Vector2u> &explodedPositions) const
    {
        /// Signed delta between the entity position and its main cell center.
        raylib::core::Vector2f centerDelta = {
            pos.x - static_cast<float>(roundedPos2D.x), pos.z - static_cast<float>(roundedPos2D.y)};
        /// Unsigned distance from the cell center to the opposite side of the entity (furthest from the center)
        raylib::core::Vector2f centerDistance = {
            abs(centerDelta.x) + size.x * 0.5f, abs(centerDelta.y) + size.z * 0.5f};

        ///// Allow debug logs to adjust the limit
        // if (centerDistance.x < 0.5f && centerDistance.y < 0.5f)
        //     return false;
        // Logger::logger.log(Logger::Severity::Debug, [&](auto &out) {
        //     out << "Living overtake an adjacent cell of (" << (centerDistance.x - 0.5f) / size.x << "%, "
        //         << (centerDistance.y - 0.5f) / size.z << "%)";
        // });

        /// (centerDistance.x - 0.5f) is the distance overtaking on the next cell since the distance from the center of
        /// the cell to the start of an other is 0.5f (all cells are of size {1, 1})
        /// We compare it with a % of the entity size to detect wether it is on the cell or not.
        if ((centerDistance.x - 0.5f) < size.x * LivingEntityExplodeLimit
            && (centerDistance.y - 0.5f) < size.z * LivingEntityExplodeLimit)
            return false;

        /// Other cell pos
        raylib::core::Vector2u adjacentCell = roundedPos2D;

        if (abs(centerDelta.x) > abs(centerDelta.y))
            adjacentCell.x += std::copysign(1, centerDelta.x);
        else
            adjacentCell.y += std::copysign(1, centerDelta.y);

        return std::find(explodedPositions.begin(), explodedPositions.end(), adjacentCell) != explodedPositions.end();
    }

    bool Bomb::placeBomb(raylib::core::Vector2u bombCell, ecs::SystemData data, Bomb::Type bombType, Identity::Id owner,
        size_t range, std::chrono::milliseconds delay, raylib::core::Vector3f velocity, bool avoidDuplicates)
    {
        raylib::core::Vector3f placedPos = {static_cast<float>(bombCell.x), 0.15f, static_cast<float>(bombCell.y)};
        auto &positions = data.getStorage<Position>();
        auto &entities = data.getResource<ecs::Entities>();

        /// Avoid multiple bombs on the same cell
        if (avoidDuplicates) {
            for (auto [bombPos, bomb] : ecs::join(positions, data.getStorage<Bomb>())) {
                (void)bomb;
                if (bombPos == placedPos)
                    return false;
            }
        }

        auto builder = entities.builder();

        (void)Bomb::setBombModel(builder, data)
            .with<Bomb>(data.getStorage<Bomb>(), bombType, owner, range, delay)
            .with<Position>(data.getStorage<Position>(), placedPos)
            .with<Collidable>(data.getStorage<Collidable>());
        if (fabsf(velocity.x) > 0.f || fabsf(velocity.z) > 0.f)
            (void)builder.with<Velocity>(data.getStorage<Velocity>(), velocity);
        builder.build();

        /// Disable collision with bomb for all player on the bomb cell
        for (auto [pos, player, playerId] : ecs::join(positions, data.getStorage<Player>(), entities))
            if (bombCell == game::Game::worldPosToMapCell(pos))
                data.getStorage<BombNoClip>()[playerId.getId()].setBombPosition(bombCell);
        return true;
    }

    void Bomb::setVelocity(ecs::SystemData data, ecs::Entity self, raylib::core::Vector3f senderVelocity)
    {
        placeBomb(game::Game::worldPosToMapCell(data.getStorage<Position>()[self.getId()]), data, type, owner, radius,
            std::chrono::duration_cast<std::chrono::milliseconds>(
                explosionDelay - (std::chrono::steady_clock::now() - placedTime)),
            senderVelocity, false);
        /// Kill static bomb
        data.getResource<ecs::Entities>().kill(self);
    }

    void Bomb::stop(ecs::SystemData data, ecs::Entity self)
    {
        placeBomb(game::Game::worldPosToMapCell(data.getStorage<Position>()[self.getId()]), data, type, owner, radius,
            std::chrono::duration_cast<std::chrono::milliseconds>(
                explosionDelay - (std::chrono::steady_clock::now() - placedTime)),
            {}, false);
        /// Kill moving bomb
        data.getResource<ecs::Entities>().kill(self);
    }

    ecs::Entities::Builder &Bomb::setBombModel(ecs::Entities::Builder &builder, ecs::SystemData data)
    {
        (void)builder.with<Color>(data.getStorage<Color>(), raylib::core::Color::WHITE)
            .with<ModelReference>(
                data.getStorage<ModelReference>(), data.getResource<game::resources::Models>().get("C4"))
            .with<Size>(data.getStorage<Size>(), 0.3f, 0.3f, 0.5f)
            .with<RotationAngle>(data.getStorage<RotationAngle>(), -90.0f)
            .with<RotationAxis>(data.getStorage<RotationAxis>(), 1.f, 0.f, 0.f);
        return builder;
    }

} // namespace game::components
