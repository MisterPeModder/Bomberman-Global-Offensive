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
    struct ItemIdentifier : public ecs::Component {
      public:
        Item::Identifier identifier;

        ItemIdentifier(Item::Identifier pIdentifier) : identifier(pIdentifier) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_ITEMS_ITEMIDENTIFIER_HPP_ */
