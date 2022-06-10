/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** DrawingCube
*/

#ifndef GAME_SYSTEMS_DRAWINGCUBE_HPP_
#define GAME_SYSTEMS_DRAWINGCUBE_HPP_

#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Cube.hpp"

namespace game
{
    struct DrawingCube : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            for (auto [cube] : ecs::join(data.getStorage<Cube>())) {
                cube.cube.draw();
            }
        }
    };
} // namespace game

#endif /* !GAME_SYSTEMS_DRAWINGCUBE_HPP_ */
