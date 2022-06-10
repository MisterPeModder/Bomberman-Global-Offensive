/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Cube
*/

#ifndef GAME_COMPONENTS_CUBE_HPP_
#define GAME_COMPONENTS_CUBE_HPP_

#include "ecs/Component.hpp"
#include "raylib/shapes/Cube.hpp"

namespace game
{
    struct Cube : public ecs::Component {
        raylib::shapes::Cube cube;

        Cube() : cube() {}
        Cube(raylib::core::Vector3 position, raylib::core::Vector3 size, Color color) : cube(position, size, color) {}
    };
} // namespace game

#endif /* !GAME_COMPONENTS_CUBE_HPP_ */
