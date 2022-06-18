/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Collidable
*/

#ifndef GAME_COMPONENTS_PLAYER_HPP_
#define GAME_COMPONENTS_PLAYER_HPP_

#include <array>
#include <chrono>
#include "Bomb.hpp"
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
        /// The different player animations
        enum class Animations : unsigned int {
            Idle_1 = 0,
            Idle_2 = 1,
            Idle_3 = 2,
            Idle_4 = 3,
            Run = 4,
            Die = 5,
            Dance_1 = 6,
            Dance_2 = 7,
            Dance_3 = 8,
            Dance_4 = 9,
        };

        struct Stats {
            /// Default speed of the player (in cells per seconds).
            static constexpr float DEFAULT_SPEED = 4.f;
            /// Current player speed.
            float speed;
            /// Current player bomb explosion range.
            size_t bombRange;
            /// Max number of bomb simulteanously placed per player.
            size_t bombLimit;
            /// If controls are inverted.
            bool inverted;
            /// If on slowness effect.
            bool slowness;

            Stats() : speed(DEFAULT_SPEED), bombRange(1), bombLimit(1), inverted(false), slowness(false) {}
        };

        /// Occurence of each item in a player inventory
        struct Inventory {
            /// Number of occurence of each item in the inventory.
            std::array<size_t, static_cast<size_t>(Item::Identifier::Count)> items;
            /// Activated items with a timer.
            std::vector<std::pair<Item::Identifier, std::chrono::steady_clock::time_point>> timedItems;

            /// Selected item (activable).
            Item::Identifier selected;

            Inventory();

            /// Get the quantity of an item in the inventory.
            ///
            /// @param itemId item identifier.
            /// @return constexpr size_t quantity of this item in the inventory.
            constexpr size_t operator[](Item::Identifier itemId) const { return items[static_cast<size_t>(itemId)]; }

            /// Get the quantity of an item in the inventory.
            ///
            /// @param itemId item identifier.
            /// @return constexpr size_t& quantity of this item in the inventory.
            constexpr size_t &operator[](Item::Identifier itemId) { return items[static_cast<size_t>(itemId)]; }

            /// Pick up an item from the map.
            ///
            /// @param player player entity id.
            /// @param itemId item identifier.
            /// @param data world data.
            void add(ecs::Entity player, Item::Identifier itemId, ecs::SystemData data);

            /// Try to use the selected activable item.
            ///
            /// @param player player entity id.
            /// @param data world data.
            /// @return true If the item was consumed.
            /// @return false If no item was consumed.
            bool useActivable(ecs::Entity player, ecs::SystemData data);

            /// Try to select the previous possessed activable item.
            /// @note Selection unchanged means there is only one or zero possessed activable item.
            ///
            /// @return true If the selection changed.
            /// @return false If the selection didn't change.
            bool selectPreviousActivable();

            /// Try to select the next possessed activable item.
            /// @note Selection unchanged means there is only one or zero possessed activable item.
            ///
            /// @return true If the selection changed.
            /// @return false If the selection didn't change.
            bool selectNextActivable();

            /// Select a specific item, even if not possessed.
            ///
            /// @return true If the selection changed.
            /// @return false If the selection didn't change.
            bool selectActivable(Item::Identifier itemId);

            /// Select the first possessed activable item.
            /// @note Does nothing if the user possess the selected item.
            void updateSelectedActivable();
        };

        /// Player stats
        Stats stats;
        /// Player items
        Inventory inventory;
        /// Number of bomb currently placed on the map.
        size_t placedBombs;
        /// Animation that is currently playing
        Animations animation;

        /// Callback of the @ref Controlable component of the players.
        ///
        /// @param self player entity
        /// @param data world data
        /// @param event action event
        /// @return true If the action was consumed.
        /// @return false If the action wasn't consumed.
        static bool handleActionEvent(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event);

        /// Construct a new Player component
        Player() : placedBombs(0), animation(Animations::Idle_1) {}

        /// Update the activated items with a timer.
        ///
        /// @param self player entity id.
        /// @param data world data.
        void updateTimedItems(ecs::Entity self, ecs::SystemData data);

        /// Place a bomb at the player position.
        ///
        /// @param self player entity
        /// @param data world data
        /// @param bombType bomb type.
        /// @return true If the action was consumed.
        /// @return false If the action wasn't consumed.
        static void placeBomb(ecs::Entity self, ecs::SystemData data, Bomb::Type bombType = Bomb::Type::Classic);

      private:
        /// Change the velocity of the player from its action values.
        ///
        /// @param self player entity
        /// @param data world data
        /// @param event action event
        static void move(ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event);
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_PLAYER_HPP_ */
