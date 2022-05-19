/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - World
*/

#include "World.hpp"

namespace ecs
{
    World::World() {}

    World::World(World const &) {}

    World::~World() {}

    void World::runSystems()
    {
        EntityAccess tmpAccess; // TO REMOVE
        for (auto &[type, system] : this->_tmpSystems)
            system->run(tmpAccess);
    }
} // namespace ecs
