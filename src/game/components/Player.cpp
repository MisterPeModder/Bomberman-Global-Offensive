/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Player
*/

#include "Player.hpp"
#include "Bomb.hpp"
#include "Collidable.hpp"
#include "Identity.hpp"
#include "Position.hpp"
#include "Size.hpp"
#include "Velocity.hpp"
#include "ecs/Storage.hpp"
#include "ecs/join.hpp"
#include "game/Engine.hpp"
#include "game/Game.hpp"
#include "game/components/Animation.hpp"
#include "game/components/Color.hpp"
#include "game/components/Model.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/Scale.hpp"
#include "game/resources/AssetMap.hpp"
#include "game/resources/GameClock.hpp"
#include "game/resources/RandomDevice.hpp"
#include "logger/Logger.hpp"
#include "raylib/model/Mesh.hpp"
#include "raylib/model/Model.hpp"

namespace game::components
{
    Player::Inventory::Inventory()
    {
        items.fill(0);
        selected = Item::Identifier::NoClip;
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
                timedItems.emplace_back(itemId, data.getResource<game::resources::GameClock>().getTime());
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
            timedItems.emplace_back(selected, data.getResource<game::resources::GameClock>().getTime());
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
        if (data.getResource<game::resources::GameClock>().isPaused() && event.action != GameAction::PAUSE)
            return false;
        if (isMoveAction(event.action))
            move(self, data, event);
        else if (event.action == GameAction::PLACE_BOMB && event.value > 0.9f)
            placeBomb(self, data);
        else if (event.action == GameAction::ACTIVATE_ITEM && event.value > 0.9f)
            data.getStorage<Player>()[self.getId()].inventory.useActivable(self, data);
        else if (event.action == GameAction::PREVIOUS_ACTIVABLE && event.value > 0.9f)
            data.getStorage<Player>()[self.getId()].inventory.selectPreviousActivable();
        else if (event.action == GameAction::NEXT_ACTIVABLE && event.value > 0.9f)
            data.getStorage<Player>()[self.getId()].inventory.selectNextActivable();
        else if (event.action == GameAction::PAUSE && event.value > 0.9f)
            data.getResource<game::resources::GameClock>().togglePause();
        else
            return false;
        return true;
    }

    void Player::move(ecs::Entity self, ecs::SystemData data, GameAction action, float value)
    {
        auto &velocity = data.getStorage<Velocity>()[self.getId()];
        auto &rAngle = data.getStorage<RotationAngle>()[self.getId()];
        auto &anim = data.getStorage<Animation>()[self.getId()];
        auto &stats = data.getStorage<Player>()[self.getId()].stats;
        auto &player = data.getStorage<Player>()[self.getId()];

        if (data.getResource<game::resources::GameClock>().getTime() < player.stats.stunEnd)
            return;

        if (value < 0.2f) {
            velocity = {0.f, 0.f, 0.f};
            if (player.animation == Animations::Run) {
                // Randomize the idle animation id
                auto &randDevice = data.getResource<game::resources::RandomDevice>();
                unsigned int randVal = randDevice.randInt(
                    static_cast<unsigned int>(Animations::Idle_1), static_cast<unsigned int>(Animations::Idle_4));

                anim.chooseAnimation(randVal);
                player.animation = Animations(randVal);
            }
        } else {
            float speed = stats.speed;

            if (stats.inverted)
                speed *= -1.f;
            if (stats.slowness)
                speed *= 0.25f;
            switch (action) {
                case GameAction::MOVE_LEFT:
                    velocity = {-speed, 0.f, 0.f};
                    rAngle.rotationAngle = 270.f;
                    break;
                case GameAction::MOVE_UP:
                    velocity = {0.f, 0.f, -speed};
                    rAngle.rotationAngle = 180.f;
                    break;
                case GameAction::MOVE_RIGHT:
                    velocity = {speed, 0.f, 0.f};
                    rAngle.rotationAngle = 90.f;
                    break;
                case GameAction::MOVE_DOWN:
                    velocity = {0.f, 0.f, speed};
                    rAngle.rotationAngle = 0.f;
                    break;
                default: break;
            }
            if (velocity != raylib::core::Vector3f(0.f, 0.f, 0.f) && player.animation != Animations::Run) {
                anim.chooseAnimation(static_cast<unsigned int>(Animations::Run));
                player.animation = Animations::Run;
            }
        }
    }

    void Player::move(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event)
    {
        auto &velocity = data.getStorage<Velocity>()[self.getId()];
        auto &rAngle = data.getStorage<RotationAngle>()[self.getId()];
        auto &anim = data.getStorage<Animation>()[self.getId()];
        auto &user = data.getResource<game::resources::EngineResource>().engine->getUsers()[event.user];
        auto &stats = data.getStorage<Player>()[self.getId()].stats;
        auto &player = data.getStorage<Player>()[self.getId()];
        GameAction bestAction = GameAction::NONE;
        float highestActionValue = 0.f;

        if (data.getResource<game::resources::GameClock>().getTime() < player.stats.stunEnd)
            return;

        for (size_t j = static_cast<size_t>(GameAction::MOVE_LEFT); j <= static_cast<size_t>(GameAction::MOVE_DOWN);
             j++) {
            GameAction current = static_cast<GameAction>(j);
            if (user.getActionValue(current) > highestActionValue) {
                bestAction = current;
                highestActionValue = user.getActionValue(current);
            }
        }
        if (highestActionValue < 0.2f) {
            velocity = {0.f, 0.f, 0.f};
            if (player.animation == Animations::Run) {
                // Randomize the idle animation id
                auto &randDevice = data.getResource<game::resources::RandomDevice>();
                unsigned int randVal = randDevice.randInt(
                    static_cast<unsigned int>(Animations::Idle_1), static_cast<unsigned int>(Animations::Idle_4));

                anim.chooseAnimation(randVal);
                player.animation = Animations(randVal);
            }
        } else {
            float speed = stats.speed;

            if (stats.inverted)
                speed *= -1.f;
            if (stats.slowness)
                speed *= 0.25f;
            switch (bestAction) {
                case GameAction::MOVE_LEFT:
                    velocity = {-speed, 0.f, 0.f};
                    rAngle.rotationAngle = 270.f;
                    break;
                case GameAction::MOVE_UP:
                    velocity = {0.f, 0.f, -speed};
                    rAngle.rotationAngle = 180.f;
                    break;
                case GameAction::MOVE_RIGHT:
                    velocity = {speed, 0.f, 0.f};
                    rAngle.rotationAngle = 90.f;
                    break;
                case GameAction::MOVE_DOWN:
                    velocity = {0.f, 0.f, speed};
                    rAngle.rotationAngle = 0.f;
                    break;
                default: break;
            }
            if (velocity != raylib::core::Vector3f(0.f, 0.f, 0.f) && player.animation != Animations::Run) {
                anim.chooseAnimation(static_cast<unsigned int>(Animations::Run));
                player.animation = Animations::Run;
            }
        }
    }

    void Player::stun(ecs::Entity self, ecs::SystemData data, std::chrono::milliseconds duration)
    {
        stats.stunEnd = data.getResource<game::resources::GameClock>().getTime() + duration;
        // Randomize the idle animation id
        auto &randDevice = data.getResource<game::resources::RandomDevice>();
        unsigned int randVal = randDevice.randInt(
            static_cast<unsigned int>(Animations::Idle_1), static_cast<unsigned int>(Animations::Idle_4));

        data.getStorage<Animation>()[self.getId()].chooseAnimation(randVal);
        data.getStorage<Velocity>()[self.getId()] = {0.f, 0.f, 0.f};
        animation = Animations(randVal);
    }

    void Player::placeBomb(ecs::Entity self, ecs::SystemData data)
    {
        auto &placer = data.getStorage<Player>()[self.getId()];

        /// Player cannot place more bomb
        if (placer.placedBombs >= placer.stats.bombLimit)
            return;
        raylib::core::Vector2u bombCell = game::Game::worldPosToMapCell(data.getStorage<Position>()[self.getId()]);

        if (!Bomb::placeBomb(bombCell, data, Bomb::Type::Classic, data.getStorage<Identity>()[self.getId()].id,
                placer.stats.bombRange))
            return;
        ++placer.placedBombs;
    }

    void Player::placeLandMine(ecs::Entity self, ecs::SystemData data)
    {
        Bomb::placeBomb(game::Game::worldPosToMapCell(data.getStorage<Position>()[self.getId()]), data,
            Bomb::Type::LandMine, data.getStorage<Identity>()[self.getId()].id, 2);
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

            if (data.getResource<game::resources::GameClock>().getTime() - pair.second >= item.duration) {
                item.onTimedOut(self, data);
                inventory.timedItems.erase(inventory.timedItems.begin() + i);
            }
        } while (i != 0);
    }
} // namespace game::components
