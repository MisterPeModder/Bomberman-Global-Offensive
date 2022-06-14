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
#include "Position.hpp"
#include "Size.hpp"
#include "Velocity.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "game/Game.hpp"

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
                case GameAction::MOVE_LEFT: velocity = {-DefaultSpeed, 0.f, 0.f}; break;
                case GameAction::MOVE_UP: velocity = {0.f, 0.f, -DefaultSpeed}; break;
                case GameAction::MOVE_RIGHT: velocity = {DefaultSpeed, 0.f, 0.f}; break;
                case GameAction::MOVE_DOWN: velocity = {0.f, 0.f, DefaultSpeed}; break;
                default: break;
            }
    }

    void Player::placeBomb(ecs::Entity self, ecs::SystemData data)
    {
        raylib::core::Vector2u bombCell = game::Game::worldPosToMapCell(data.getStorage<Position>()[self.getId()]);
        raylib::core::Vector3f placedPos = {static_cast<float>(bombCell.x), 0.5f, static_cast<float>(bombCell.y)};

        /// Avoid multiple bombs on the same cell
        for (auto [bombPos, bomb] : ecs::join(data.getStorage<Position>(), data.getStorage<Bomb>())) {
            (void)bomb;
            if (bombPos == placedPos)
                return;
        }

        data.getResource<ecs::Entities>()
            .builder()
            .with<Bomb>(data.getStorage<Bomb>(), 2)
            .with<Position>(data.getStorage<Position>(), placedPos)
            .with<Size>(data.getStorage<Size>(), 0.5f, 0.f, 0.5f)
            .with<Collidable>(data.getStorage<Collidable>())
            .build();
        data.getStorage<BombNoClip>()[self.getId()].setBombPosition(bombCell);
    }
} // namespace game::components
