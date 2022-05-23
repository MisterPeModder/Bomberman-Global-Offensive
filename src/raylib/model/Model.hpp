/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Model
*/

#ifndef RAYLIB_MODEL_MODEL_HPP_
#define RAYLIB_MODEL_MODEL_HPP_

extern "C"
{
#include <raylib.h>
}

#include <string>
#include "raylib/core/Vector3.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/model/BoundingBox.hpp"

namespace raylib
{
    namespace model
    {
        class Model {
          public:
            Model(const std::string &modelPath);

            ~Model();

            void draw(raylib::core::Vector3 position, float scale, raylib::core::Color tint) const;

            void draw(raylib::core::Vector3 position, raylib::core::Vector3 rotationAxis, float rotationAngle, raylib::core::Vector3 scale, raylib::core::Color tint) const;

            void drawWires(raylib::core::Vector3 position, float scale, raylib::core::Color tint) const;

            void drawWires(raylib::core::Vector3 position, raylib::core::Vector3 rotationAxis, float rotationAngle, raylib::core::Vector3 scale, raylib::core::Color tint) const;

            BoundingBox getBoundingBox() const;

            ::Model toRaylib() const;

            bool checkCollision(const Model &other);

            bool checkCollision(const BoundingBox &other);

          protected:
          private:
            ::Model _model;
        };
    }
}

#endif /* !RAYLIB_MODEL_MODEL_HPP_ */
