/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Item
*/

#ifndef GAME_COMPONENTS_ITEMS_ITEM_HPP_
#define GAME_COMPONENTS_ITEMS_ITEM_HPP_

#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include "ecs/System.hpp"
#include "game/resources/RandomDevice.hpp"
#include "raylib/core/Vector2.hpp"

#include <array>
#include <chrono>
#include <functional>
#include <string_view>

namespace game::components
{
    struct Item : public ecs::Component {
      public:
        /// Function called when item is applied
        using OnApply = std::function<bool(ecs::Entity, ecs::SystemData)>;
        /// Function called for timed item on timer end
        using OnTimedOut = std::function<void(ecs::Entity, ecs::SystemData)>;
        /// Item Type.
        enum class Type { PowerUp, PowerDown, Activable };
        /// Item identifiers
        enum class Identifier {
            /// Power Up
            SpeedShoes,
            FireUp,
            BombUp,
            KickShoes,
            /// Power Down
            ChainBall,
            FireDown,
            BombDown,
            InvertedControls,
            /// Activable
            NoClip,
            LandMine,
            StunGrenade,
            SmokeGrenade,
            Punch,
            Count,
        };

        static std::array<std::string_view, static_cast<size_t>(Identifier::Count)> NAMES;

        /// @ref Type.
        Type type;

        /// @ref Identifier
        Identifier identifier;

        /// Max number of this item (effect) stacked by a player.
        /// @note 0 means unlimited.
        size_t maxStack;

        /// Name of the item.
        std::string name;

        /// Duration of the item.
        /// @note 0 means infinite.
        std::chrono::milliseconds duration;

        /// Chance to get this item when dropping an item from its type. ([0-100])
        /// @warning the sum of all the drop rates of the items with the same type @b must be equal to 100.
        unsigned int dropRate;

        /// Function called when the player use the item.
        /// @note PowerUp/Down are used on pickup.
        OnApply onApply;

        /// Function called for timed item on timer end
        /// @note Not used if @c duration is infinite (0).
        OnTimedOut onTimedOut;

        /// Spawn a random item on a given cell.
        /// @note Doesn't always spawn an item, follow the item drop rate from crates.
        ///
        /// @param data world data.
        /// @param cell item position.
        /// @retval true if an item was created.
        /// @retval false if no item was created.
        static bool spawnRandomItem(ecs::SystemData data, raylib::core::Vector2u cell);

        /// Spawns a specific item on a given cell.
        ///
        /// @param item The item to spawn.
        /// @param data world data.
        /// @param cell Item position.
        static void spawnItem(Identifier item, ecs::SystemData data, raylib::core::Vector2u cell);

        /// Get an item from its identifier.
        ///
        /// @param identifier item identifier.
        /// @return const Item& item.
        static const Item &getItem(Identifier identifier);

        /// Get an item from its name.
        ///
        /// @param name The item's name.
        ///
        /// @returns A pointer to the item if found, or @c nullptr if not.
        static const Item *getItem(std::string_view name);

        /// First activable item.
        /// @note The last is the item preceeding @ref Identifier::Count
        static constexpr Identifier FIRST_ACTIVABLE = Identifier::NoClip;

        /// Get the activable item following @c current.
        /// @note This function consider the activable items as a circular list, beware infinity loops.
        ///
        /// @param current current item.
        /// @return Identifier item following @c current.
        static Identifier nextActivable(Identifier current);

        /// Get the activable item preceeding @c current.
        /// @note This function consider the activable items as a circular list, beware infinity loops.
        ///
        /// @param current current item.
        /// @return Identifier item preceeding @c current.
        static Identifier previousActivable(Identifier current);

      private:
        Item(){};

        //////// Items
        /// Power Ups
        static Item SpeedShoes();
        static Item FireUp();
        static Item BombUp();
        static Item KickShoes();
        /// Power Downs
        static Item ChainBall();
        static Item FireDown();
        static Item BombDown();
        static Item InvertedControls();
        /// Activable
        static Item NoClip();
        static Item LandMine();
        static Item StunGrenade();
        static Item SmokeGrenade();
        static Item Punch();

        static constexpr size_t POWER_UP_COUNT = 4;
        static constexpr size_t POWER_DOWN_COUNT = 4;
        static constexpr size_t ACTIVABLE_COUNT = 5;

        static std::array<Identifier, POWER_UP_COUNT> powerUps;
        static std::array<Identifier, POWER_DOWN_COUNT> powerDowns;
        static std::array<Identifier, ACTIVABLE_COUNT> activables;
        static std::array<Item, static_cast<size_t>(Identifier::Count)> items;
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_ITEMS_ITEM_HPP_ */
