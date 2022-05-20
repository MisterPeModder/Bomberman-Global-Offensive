/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Entity Resource
*/

#ifndef ECS_ENTITIES_HPP_
#define ECS_ENTITIES_HPP_

#include "ecs/Entity.hpp"
#include "ecs/world/Resource.hpp"

#include <vector>

namespace ecs
{
    class Entities : public Resource {
      public:
        explicit Entities();

        Entity create();

        bool erase(Entity entity) noexcept;

        Entity get(Entity::Index id) noexcept;

        bool isAlive(Entity entity) noexcept;

      private:
        std::vector<Entity::Generation> _generations;
        std::vector<bool> _alive;
    };
} // namespace ecs

#endif // !defined(ECS_ENTITIES_HPP_)
