/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Collidable
*/

#ifndef GAME_COMPONENTS_PLAYER_HPP_
#define GAME_COMPONENTS_PLAYER_HPP_

#include <array>
#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "game/Users.hpp"
#include "items/Item.hpp"
#include "items/ItemIdentifier.hpp"

namespace game::components
{
    /// Player marker.
    struct Player : public ecs::Component {
        struct Stats {
            /// Default speed of the player (in cells per seconds).
            static constexpr float DEFAULT_SPEED = 4.f;
            /// Current player speed.
            float speed;
            /// Current player bomb explosion range.
            size_t bombRange;
            /// Max number of bomb simulteanously placed per player.
            size_t bombLimit;

            Stats() : speed(DEFAULT_SPEED), bombRange(1), bombLimit(2) {}
        };

        /// Occurence of each item in a player inventory
        struct Inventory {
            /// Number of occurence of each item in the inventory.
            std::array<size_t, static_cast<size_t>(Item::Identifier::Count)> items;

            Inventory() { items.fill(0); }
        };

        /// Player stats
        Stats stats;
        /// Player items
        Inventory inventory;
        /// Number of bomb currently placed on the map.
        size_t placedBombs;

        /// Callback of the @ref Controlable component of the players.
        ///
        /// @param self player entity
        /// @param data world data
        /// @param event action event
        /// @return true If the action was consumed.
        /// @return false If the action wasn't consumed.
        static bool handleActionEvent(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event);

        /// Construct a new Player component
        Player() : placedBombs(0) {}

        /// Pick up an item from the map.
        ///
        /// @param self player entity id.
        /// @param itemId item identifier.
        /// @param data world data.
        void pickupItem(ecs::Entity self, Item::Identifier itemId, ecs::SystemData data);

      private:
        /// Change the velocity of the player from its action values.
        ///
        /// @param self player entity
        /// @param data world data
        /// @param event action event
        static void move(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event);

        /// Place a bomb at the player position.
        ///
        /// @param self player entity
        /// @param data world data
        /// @return true If the action was consumed.
        /// @return false If the action wasn't consumed.
        static void placeBomb(ecs::Entity self, ecs::SystemData data);
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_PLAYER_HPP_ */
