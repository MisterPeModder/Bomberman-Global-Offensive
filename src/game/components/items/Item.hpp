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
#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include "ecs/System.hpp"

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

        /// Chance to get this item when dropping an item from its type.
        float dropRate;

        /// Function called when the player use the item.
        /// @note PowerUp/Down are used on pickup.
        OnApply onApply;

        static std::vector<Item> powerUps;
        static std::vector<Item> powerDowns;
        static std::vector<Item> activables;

      private:
        Item(){};

        static Item SpeedShoes();
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_ITEMS_ITEM_HPP_ */
