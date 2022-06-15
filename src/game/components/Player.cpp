/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Player
*/

#include "Player.hpp"
#include "Bomb.hpp"
#include "BombNoClip.hpp"
#include "Collidable.hpp"
#include "Identity.hpp"
#include "Position.hpp"
#include "Size.hpp"
#include "Velocity.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "raylib/model/Mesh.hpp"
#include "raylib/model/Model.hpp"
#include "game/components/Scale.hpp"
#include "game/components/Color.hpp"
#include "game/components/Model.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/Game.hpp"
#include "game/resources/AssetMap.hpp"

namespace game::components
{
    bool Player::handleActionEvent(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event)
    {
        if (isMoveAction(event.action))
            move(self, data, event);
        else if (event.action == GameAction::PLACE_BOMB && event.value > 0.9f)
            placeBomb(self, data);
        else
            return false;
        return true;
    }

    void Player::move(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event)
    {
        auto &velocity = data.getStorage<Velocity>()[self.getId()];
        auto &user = data.getResource<Users>()[event.user];
        auto &stats = data.getStorage<Player>()[self.getId()].stats;
        GameAction bestAction = GameAction::NONE;
        float highestActionValue = 0.f;

        for (size_t j = static_cast<size_t>(GameAction::MOVE_LEFT); j <= static_cast<size_t>(GameAction::MOVE_DOWN);
            j++) {
            GameAction current = static_cast<GameAction>(j);
            if (user.getActionValue(current) > highestActionValue) {
                bestAction = current;
                highestActionValue = user.getActionValue(current);
            }
        }
        if (highestActionValue < 0.2f)
            velocity = {0.f, 0.f};
        else
            switch (bestAction) {
                case GameAction::MOVE_LEFT: velocity = {-stats.speed, 0.f, 0.f}; break;
                case GameAction::MOVE_UP: velocity = {0.f, 0.f, -stats.speed}; break;
                case GameAction::MOVE_RIGHT: velocity = {stats.speed, 0.f, 0.f}; break;
                case GameAction::MOVE_DOWN: velocity = {0.f, 0.f, stats.speed}; break;
                default: break;
            }
    }

    void Player::placeBomb(ecs::Entity self, ecs::SystemData data)
    {
        auto &player = data.getStorage<Player>()[self.getId()];

        /// Player cannot place more bomb
        if (player.placedBombs >= player.stats.bombLimit)
            return;
        raylib::core::Vector2u bombCell = game::Game::worldPosToMapCell(data.getStorage<Position>()[self.getId()]);
        raylib::core::Vector3f placedPos = {static_cast<float>(bombCell.x), 0.5f, static_cast<float>(bombCell.y)};

        /// Avoid multiple bombs on the same cell
        for (auto [bombPos, bomb] : ecs::join(data.getStorage<Position>(), data.getStorage<Bomb>())) {
            (void)bomb;
            if (bombPos == placedPos)
                return;
        }

        auto bomb = data.getResource<ecs::Entities>()
            .builder()
            .with<Bomb>(data.getStorage<Bomb>(), data.getStorage<Identity>()[self.getId()].id, player.stats.bombRange)
            //.with<Scale>(data.getStorage<Scale>(), 1.f)
            .with<Color>(data.getStorage<Color>(), raylib::core::Color::WHITE)
            .with<Model>(data.getStorage<Model>(), "assets/items/c4.iqm")
            .with<Position>(data.getStorage<Position>(), placedPos)
            .with<Size>(data.getStorage<Size>(), .3f, .3f, .3f)
            .with<Collidable>(data.getStorage<Collidable>())
            .with<RotationAngle>(data.getStorage<RotationAngle>(), 0.0f)
            .with<RotationAxis>(data.getStorage<RotationAxis>(), 0.f, 0.f, 0.f)
            .build();
        data.getStorage<Model>()[bomb.getId()].setMaterialMapTexture(data.getResource<resources::Textures>().get("C4"), 0, MATERIAL_MAP_DIFFUSE);
        data.getStorage<BombNoClip>()[self.getId()].setBombPosition(bombCell);

        ++player.placedBombs;
    }
} // namespace game::components
