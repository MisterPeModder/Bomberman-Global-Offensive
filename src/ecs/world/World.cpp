/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - World
*/

#include "ecs/world/World.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Entities.hpp"
#include "ecs/system/SystemData.hpp"
#include "ecs/system/SystemTag.hpp"

namespace ecs
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Instantiation
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    World::World() { this->addResource<Entities>(); }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Populating
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    World::EntityBuilder::EntityBuilder(World &outer) : _outer(outer), _builder(outer.getResource<Entities>().builder())
    {
    }

    Entity World::EntityBuilder::build() { return this->_builder.build(); }

    World::EntityBuilder World::addEntity() { return EntityBuilder(*this); }

    void World::clear()
    {
        this->_resources.clear();
        this->_systems.clear();
        this->_storages.clear();
        this->addResource<Entities>();
    }

    void World::maintain()
    {
        std::vector<Entity> toRemove = this->getResource<Entities>().maintain();

        for (auto &[type, system] : this->_storages.getInner())
            system->maintain(toRemove);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Running
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void World::runSystems()
    {
        for (auto &[type, system] : this->_systems.getInner())
            system->run(SystemData(*this));
    }

    void World::runSystems(SystemTag const &tag)
    {
        for (auto &type : tag._types)
            this->_systems.get(type, "tried to run unregistered system").run(SystemData(*this));
    }

    void World::runSystem(System &system) { system.run(SystemData(*this)); }
} // namespace ecs
