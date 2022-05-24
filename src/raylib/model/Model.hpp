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
        /// The Model class ; it shouldn't be created multiple times for the same file
        class Model {
          public:
            /// Model constructor. Used to initialize a 3D model from a file
            /// File format accepted: obj and probably some other
            ///
            /// @param modelPath the relative path to the 3D model to import
            Model(const std::string &modelPath);

            /// Model destructor
            ~Model();

            /// Deleted copy constructor because it makes no sense to load the same file multiple simes
            Model(const Model &other) = delete;

            /// Deleted copy operator because it makes no sense to load the same file multiple simes
            Model &operator=(const Model &other) = delete;

            /// Draw the model the basic way
            ///
            /// @param position Where the model will be drawn
            /// @param scale The scale to apply to the model when drawing it
            /// @param tint The color tint to apply to the model (leave the default value to disable)
            void draw(raylib::core::Vector3 position, float scale, raylib::core::Color tint = {255, 255, 255, 255}) const;

            /// Draw the model the advanced way
            ///
            /// @param position Where the model will be drawn
            /// @param rotationAxis where to place the rotation axis used by the rotationAngle param
            /// @param rotationAngle the rotation angle
            /// @param scale The scale to apply to the model when drawing it
            /// @param tint The color tint to apply to the model (leave the default value to disable)
            void draw(raylib::core::Vector3 position, raylib::core::Vector3 rotationAxis, float rotationAngle, raylib::core::Vector3 scale, raylib::core::Color tint = {255, 255, 255, 255}) const;

            /// Draw the model's wires the basic way
            ///
            /// @param position Where the wires will be drawn
            /// @param scale The scale to apply to the wires when drawing it
            /// @param tint The color tint to apply to the wires (leave the default value to disable)
            void drawWires(raylib::core::Vector3 position, float scale, raylib::core::Color tint = {255, 255, 255, 255}) const;

            /// Draw the model's wires the advanced way
            ///
            /// @param position Where the wires will be drawn
            /// @param rotationAxis where to place the rotation axis used by the rotationAngle param
            /// @param rotationAngle the rotation angle
            /// @param scale The scale to apply to the wires when drawing it
            /// @param tint The color tint to apply to the wires (leave the default value to disable)
            void drawWires(raylib::core::Vector3 position, raylib::core::Vector3 rotationAxis, float rotationAngle, raylib::core::Vector3 scale, raylib::core::Color tint = {255, 255, 255, 255}) const;

            /// Gets the bounding box of the model
            ///
            /// @return The bounding box of the model
            BoundingBox getBoundingBox() const;

            /// Gets the C Raylib modifiable version of the model
            ///
            /// @return The raylib version of the model
            ::Model &asRaylib();

            /// Gets the C Raylib const version of the model
            ///
            /// @return The raylib version of the model
            ::Model asRaylib() const;

            /// Checks collision with another model
            ///
            /// @param other The other model to check the collisions with
            ///
            /// @retval true if the two models collides
            /// @retval false if the two models doesn't collide
            bool checkCollision(const Model &other);

            /// Checks collision with a bounding box
            ///
            /// @param other The bounding box to check the collisions with
            ///
            /// @retval true if the model collides with the bounding box
            /// @retval false if the model doesn't collide with the bounding box
            bool checkCollision(const BoundingBox &otherBox);

          private:
            ::Model _model;
        };
    }
}

#endif /* !RAYLIB_MODEL_MODEL_HPP_ */
