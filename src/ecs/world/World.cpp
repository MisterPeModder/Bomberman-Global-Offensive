/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - World
*/

#include "ecs/world/World.hpp"
#include "ecs/SystemData.hpp"
#include "ecs/world/Entities.hpp"

namespace ecs
{
    World::World() { this->addResource<Entities>(); }

    void World::runSystems()
    {
        for (auto &[type, system] : this->_systems.getInner())
            system->run(SystemData(*this));
    }

    void World::runSystem(System &system) { system.run(SystemData(*this)); }
} // namespace ecs
