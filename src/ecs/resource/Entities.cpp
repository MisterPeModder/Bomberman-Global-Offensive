/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Entity Resource
*/

#include "ecs/resource/Entities.hpp"

#include <algorithm>

namespace ecs
{
    Entities::Builder::Builder(Entities &outer) : _outer(outer), _entity(outer.create(false)), _consumed(false) {}

    Entity Entities::Builder::build()
    {
        this->checkConsumed();
        this->_consumed = true;
        this->_outer._alive[this->_entity.getId()] = true;
        return this->_entity;
    }

    void Entities::Builder::checkConsumed()
    {
        if (this->_consumed)
            throw std::logic_error("Attempted to used entity builder after a call to build()");
    }

    Entities::Entities() {}

    Entity Entities::create() { return this->create(true); }

    Entity Entities::create(bool alive)
    {
        auto begin = this->_alive.cbegin();
        auto end = this->_alive.cend();
        auto firstDead = std::find(begin, end, false);

        if (firstDead == end) {
            // If there is not empty slot, add one the end
            Entity::Index id = this->_alive.size();

            this->_generations.push_back(1);
            this->_alive.push_back(alive);
            return Entity(id, 1);
        } else {
            // If there is a slot available, bump the generation count by one and use that slot.
            Entity::Index id = static_cast<Entity::Index>(firstDead - begin);

            this->_generations[id] += 1;
            this->_alive[id] = true;
            return Entity(id, this->_generations[id]);
        }
    }

    Entities::Builder Entities::builder() { return Builder(*this); }

    bool Entities::erase(Entity entity) noexcept
    {
        if (entity.getId() >= this->_generations.size())
            return true;
        if (this->_generations[entity.getId()] != entity.getGeneration())
            return false;
        if (entity.getId() + 1 == this->_generations.size()) {
            this->_alive.pop_back();
            this->_generations.pop_back();
        } else {
            this->_alive[entity.getId()] = false;
        }
        return true;
    }

    Entity Entities::get(Entity::Index id) noexcept
    {
        if (id >= this->_generations.size())
            return Entity(id, 0);
        return Entity(id, this->_generations[id]);
    }

    bool Entities::isAlive(Entity entity) noexcept
    {
        return entity.getGeneration() > 0 && entity.getId() < this->_generations.size() && this->_alive[entity.getId()];
    }
} // namespace ecs
