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
#include "raylib.h"
}

#include <string>
#include "Vector3.hpp"
#include "Color.hpp"
#include "BoundingBox.hpp"

namespace raylib
{
    namespace model
    {
        class Model {
          public:
            Model(std::string &modelPath);
            ~Model();

            void draw(raylib::core::Vector3 position, float scale, raylib::core::Color tint);
            void draw(raylib::core::Vector3 position, raylib::core::Vector3 rotationAxis, float rotationAngle, raylib::core::Vector3 scale, raylib::core::Color tint);
            
            void drawWires(raylib::core::Vector3 position, float scale, raylib::core::Color tint);
            void drawWires(raylib::core::Vector3 position, raylib::core::Vector3 rotationAxis, float rotationAngle, raylib::core::Vector3 scale, raylib::core::Color tint);
            
            ::BoundingBox getBoundingBox() const;

          protected:
          private:
            ::Model _model;
        };
    }
}

#endif /* !RAYLIB_MODEL_MODEL_HPP_ */
