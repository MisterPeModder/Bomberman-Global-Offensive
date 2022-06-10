/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Temp
*/

#ifndef TEMP_HPP_
#define TEMP_HPP_

#include "Position.hpp"
#include "Size.hpp"
#include "ecs/Component.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/shapes/Cube.hpp"

namespace game
{
    struct CubeColor : public ecs::Component, public raylib::core::Color {
        CubeColor(unsigned char cr, unsigned char cg, unsigned char cb, unsigned char ca)
            : raylib::core::Color(cr, cg, cb, ca)
        {
        }
        CubeColor(const raylib::core::Color &other) : raylib::core::Color(other) {}
    };

    struct Cube : public ecs::Component {
        raylib::shapes::Cube cube;

        Cube() : cube() {}
        Cube(raylib::core::Vector3 position, raylib::core::Vector3 size, Color color) : cube(position, size, color) {}
    };

    struct ChangeCube : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            for (auto [cube, pos, col, size] : ecs::join(data.getStorage<Cube>(), data.getStorage<Position>(),
                     data.getStorage<CubeColor>(), data.getStorage<Size>())) {
                cube.cube.setPosition(pos);
                cube.cube.setColor(col);
                cube.cube.setSize(size);
            }
        }
    };

    struct DrawingCube : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            for (auto [cube] : ecs::join(data.getStorage<Cube>())) {
                cube.cube.draw();
            }
        }
    };

} // namespace game

#endif /* !TEMP_HPP_ */
