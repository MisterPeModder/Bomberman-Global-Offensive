/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Item
*/

#ifndef GAME_COMPONENTS_ITEMS_ITEMIDENTIFIER_HPP_
#define GAME_COMPONENTS_ITEMS_ITEMIDENTIFIER_HPP_

#include "Item.hpp"

namespace game::components
{
    /// Item identifier component
    /// @note use @ref Item::getItem() to get the item from the identifier.
    struct ItemIdentifier : public ecs::Component {
      public:
        /// Item identifier
        Item::Identifier identifier;

        /// Construct a new Item Identifier component
        ItemIdentifier(Item::Identifier pIdentifier) : identifier(pIdentifier) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_ITEMS_ITEMIDENTIFIER_HPP_ */
