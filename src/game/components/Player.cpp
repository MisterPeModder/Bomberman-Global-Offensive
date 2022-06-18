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
#include "game/Engine.hpp"
#include "game/Game.hpp"
#include "game/components/Color.hpp"
#include "game/components/Model.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Scale.hpp"
#include "game/resources/AssetMap.hpp"
#include "logger/Logger.hpp"
#include "raylib/model/Mesh.hpp"
#include "raylib/model/Model.hpp"

namespace game::components
{
    Player::Inventory::Inventory()
    {
        items.fill(0);
        selected = Item::Identifier::LandMine;
    }

    void Player::Inventory::add(ecs::Entity player, Item::Identifier itemId, ecs::SystemData data)
    {
        const Item &item = Item::getItem(itemId);
        auto &count = (*this)[itemId];

        /// Item has a stack limit and we reached it
        if (item.maxStack && count >= item.maxStack)
            return;
        /// Item has no effect (rejected).
        if ((item.type == Item::Type::PowerUp || item.type == Item::Type::PowerDown)) {
            if (!item.onApply(player, data))
                return;
            /// Item has a duration.
            if (item.duration != std::chrono::milliseconds::zero())
                timedItems.emplace_back(itemId, std::chrono::steady_clock::now());
        }
        ++count;
        Logger::logger.log(Logger::Severity::Debug, [&](auto &out) {
            out << "Player entity " << player.getId() << " pick up item '" << item.name << "', " << count << "/"
                << item.maxStack << " in inventory ";
        });
        updateSelectedActivable();
    }

    bool Player::Inventory::useActivable(ecs::Entity player, ecs::SystemData data)
    {
        auto &count = (*this)[selected];

        /// Don't have any activable item
        if (count == 0)
            return false;
        const Item &item = Item::getItem(selected);

        /// Item couldn't be activated, don't remove it.
        if (!item.onApply(player, data))
            return false;
        --count;
        /// Item has a duration.
        if (item.duration != std::chrono::milliseconds::zero())
            timedItems.emplace_back(selected, std::chrono::steady_clock::now());
        Logger::logger.log(Logger::Severity::Debug, [&](auto &out) {
            out << "Player entity " << player.getId() << " activated item '" << item.name << "', " << count
                << " left in inventory.";
        });
        if (!count)
            updateSelectedActivable();
        return true;
    }

    bool Player::Inventory::selectActivable(Item::Identifier itemId)
    {
        if (itemId == selected)
            return false;
        selected = itemId;
        Logger::logger.log(Logger::Severity::Debug,
            [&](auto &out) { out << "Player activable item set to '" << Item::getItem(selected).name; });
        return true;
    }

    bool Player::Inventory::selectPreviousActivable()
    {
        Item::Identifier current = Item::previousActivable(selected);

        while (!(*this)[current] && current != selected)
            current = Item::previousActivable(current);
        return selectActivable(current);
    }
    bool Player::Inventory::selectNextActivable()
    {
        Item::Identifier current = Item::nextActivable(selected);

        while (!(*this)[current] && current != selected)
            current = Item::nextActivable(current);
        return selectActivable(current);
    }
    void Player::Inventory::updateSelectedActivable()
    {
        if ((*this)[selected])
            return;
        selectNextActivable();
    }

    bool Player::handleActionEvent(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event)
    {
        if (isMoveAction(event.action))
            move(self, data, event);
        else if (event.action == GameAction::PLACE_BOMB && event.value > 0.9f)
            placeBomb(self, data);
        else if (event.action == GameAction::ACTIVATE_ITEM && event.value > 0.9f)
            data.getStorage<Player>()[self.getId()].inventory.useActivable(self, data);
        else
            return false;
        return true;
    }

    void Player::move(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event)
    {
        auto &velocity = data.getStorage<Velocity>()[self.getId()];
        auto &user = data.getResource<game::resources::EngineResource>().engine->getUsers()[event.user];
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
        else {
            float speed = stats.speed;

            if (stats.inverted)
                speed *= -1.f;
            if (stats.slowness)
                speed *= 0.25f;
            switch (bestAction) {
                case GameAction::MOVE_LEFT: velocity = {-speed, 0.f, 0.f}; break;
                case GameAction::MOVE_UP: velocity = {0.f, 0.f, -speed}; break;
                case GameAction::MOVE_RIGHT: velocity = {speed, 0.f, 0.f}; break;
                case GameAction::MOVE_DOWN: velocity = {0.f, 0.f, speed}; break;
                default: break;
            }
        }
    }

    void Player::placeBomb(ecs::Entity self, ecs::SystemData data, Bomb::Type bombType)
    {
        auto &players = data.getStorage<Player>();
        auto &positions = data.getStorage<Position>();
        auto &placer = players[self.getId()];

        if (bombType == Bomb::Type::Classic) {
            /// Player cannot place more bomb
            if (placer.placedBombs >= placer.stats.bombLimit)
                return;
        }
        raylib::core::Vector2u bombCell = game::Game::worldPosToMapCell(positions[self.getId()]);
        raylib::core::Vector3f placedPos = {static_cast<float>(bombCell.x), 0.15f, static_cast<float>(bombCell.y)};

        /// Avoid multiple bombs on the same cell
        for (auto [bombPos, bomb] : ecs::join(positions, data.getStorage<Bomb>())) {
            (void)bomb;
            if (bombPos == placedPos)
                return;
        }

        auto builder = data.getResource<ecs::Entities>().builder();

        Bomb::setBombModel(builder, data)
            .with<Bomb>(
                data.getStorage<Bomb>(), bombType, data.getStorage<Identity>()[self.getId()].id, placer.stats.bombRange)
            .with<Position>(data.getStorage<Position>(), placedPos)
            .with<Collidable>(data.getStorage<Collidable>())
            .build();
        if (bombType == Bomb::Type::Classic)
            ++placer.placedBombs;
        /// Disable collision with bomb for all player on the bomb cell
        for (auto [pos, player, playerId] : ecs::join(positions, players, data.getResource<ecs::Entities>()))
            if (bombCell == game::Game::worldPosToMapCell(pos))
                data.getStorage<BombNoClip>()[playerId.getId()].setBombPosition(bombCell);
    }

    void Player::updateTimedItems(ecs::Entity self, ecs::SystemData data)
    {
        if (inventory.timedItems.empty())
            return;
        size_t i = inventory.timedItems.size();

        do {
            --i;
            auto &pair = inventory.timedItems[i];
            auto &item = Item::getItem(pair.first);

            if (std::chrono::steady_clock::now() - pair.second >= item.duration) {
                item.onTimedOut(self, data);
                inventory.timedItems.erase(inventory.timedItems.begin() + i);
            }
        } while (i != 0);
    }
} // namespace game::components
