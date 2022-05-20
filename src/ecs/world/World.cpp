/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - World
*/

#include "ecs/world/World.hpp"
#include "ecs/world/Entities.hpp"

namespace ecs
{
    World::World() { this->addResource<Entities>(); }

    World::World(World const &) {}

    World::~World() {}

    void World::runSystems()
    {
        EntityAccess tmpAccess; // TO REMOVE
        for (auto &[type, system] : this->_tmpSystems)
            system->run(tmpAccess);
    }
} // namespace ecs
