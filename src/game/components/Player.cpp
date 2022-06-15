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
#include "game/Game.hpp"
#include "logger/Logger.hpp"

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
            velocity = {0.f, 0.f, 0.f};
        else
            switch (bestAction) {
                case GameAction::MOVE_LEFT: velocity = {-stats.speed, 0.f, 0.f}; break;
                case GameAction::MOVE_UP: velocity = {0.f, 0.f, -stats.speed}; break;
                case GameAction::MOVE_RIGHT: velocity = {stats.speed, 0.f, 0.f}; break;
                case GameAction::MOVE_DOWN: velocity = {0.f, 0.f, stats.speed}; break;
                default: break;
            }
        if (stats.inverted)
            velocity *= {-1.f, 0.f, -1.f};
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

        data.getResource<ecs::Entities>()
            .builder()
            .with<Bomb>(data.getStorage<Bomb>(), data.getStorage<Identity>()[self.getId()].id, player.stats.bombRange)
            .with<Position>(data.getStorage<Position>(), placedPos)
            .with<Size>(data.getStorage<Size>(), 0.5f, 0.f, 0.5f)
            .with<Collidable>(data.getStorage<Collidable>())
            .build();
        data.getStorage<BombNoClip>()[self.getId()].setBombPosition(bombCell);
        ++player.placedBombs;
    }

    void Player::pickupItem(ecs::Entity self, Item::Identifier itemId, ecs::SystemData data)
    {
        const Item &item = Item::getItem(itemId);
        auto &count = inventory.items[static_cast<size_t>(itemId)];

        /// Item has a stack limit and we reached it
        if (item.maxStack && count >= item.maxStack)
            return;
        /// Item has no effect (rejected).
        if ((item.type == Item::Type::PowerUp || item.type == Item::Type::PowerDown) && !item.onApply(self, data))
            return;
        ++count;
        /// Item has a duration.
        if (item.duration != std::chrono::milliseconds::zero())
            inventory.timedItems.emplace_back(itemId, std::chrono::steady_clock::now());
        Logger::logger.log(Logger::Severity::Debug, [&](auto &out) {
            out << "Player entity " << self.getId() << " pick up item '" << item.name << "', " << count << "/"
                << item.maxStack << " in inventory ";
        });
    }

    void Player::updateTimedItems(ecs::Entity self, ecs::SystemData data)
    {
        if (inventory.timedItems.empty())
            return;
        size_t i = inventory.timedItems.size() - 1;

        do {
            auto &pair = inventory.timedItems[i];
            auto &item = Item::getItem(pair.first);

            if (std::chrono::steady_clock::now() - pair.second >= item.duration) {
                item.onTimedOut(self, data);
                inventory.timedItems.erase(inventory.timedItems.begin() + i);
            }
            --i;
        } while (i != 0);
    }
} // namespace game::components
