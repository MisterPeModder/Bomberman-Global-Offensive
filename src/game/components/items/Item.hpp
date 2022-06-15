/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Item
*/

#ifndef GAME_COMPONENTS_ITEMS_ITEM_HPP_
#define GAME_COMPONENTS_ITEMS_ITEM_HPP_

#include <chrono>
#include <functional>
#include <vector>
#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include "ecs/System.hpp"
#include "raylib/core/Vector2.hpp"

namespace game::components
{
    struct Item : public ecs::Component {
      public:
        /// Function called when item is applied
        using OnApply = std::function<void(ecs::Entity, ecs::SystemData)>;
        /// Item Type.
        enum class Type { PowerUp, PowerDown, Activable };
        /// Item identifiers
        enum class Identifier {
            SpeedShoes,
        };

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

        static std::vector<Identifier> powerUps;
        static std::vector<Identifier> powerDowns;
        static std::vector<Identifier> activables;
        static std::vector<Item> items;

        static bool spawnRandomItem(ecs::SystemData data, raylib::core::Vector2u cell);

        static const Item &getItem(Identifier identifier);

      private:
        Item(){};

        static void spawnItem(Identifier item, ecs::SystemData data, raylib::core::Vector2u cell);

        static Item SpeedShoes();
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_ITEMS_ITEM_HPP_ */
