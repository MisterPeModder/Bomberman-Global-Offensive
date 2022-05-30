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

    Entities::Entities() : _alive(0) { this->_alive.push(false); }

    Entity Entities::create() { return this->create(true); }

    Entity Entities::create(bool alive)
    {
        // SAFETY: firstUnset works because there is always a sentinel zero bit at the end of the 'alive' set.
        std::size_t firstDead = this->_alive.firstUnset();

        if (firstDead == this->_generations.size()) {
            // If there is not empty slot (apart from the sentinel), add one to the end
            this->_generations.push_back(1);
            this->_alive[firstDead] = alive;
            this->_alive.push(false);
            return Entity(firstDead, 1);
        } else {
            // If there is a slot available, bump the generation count by one and use that slot.
            this->_generations[firstDead] += 1;
            this->_alive[firstDead] = alive;
            return Entity(firstDead, this->_generations[firstDead]);
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
            this->_alive.pop();
            this->_generations.pop_back();
        }
        this->_alive[entity.getId()] = false;
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
