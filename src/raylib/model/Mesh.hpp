/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Mesh
*/

#ifndef RAYLIB_CORE_MESH_HPP_
#define RAYLIB_CORE_MESH_HPP_

extern "C"
{
#include <raylib.h>
}
#include "raylib/core/Vector3.hpp"
#include "raylib/textures/Image.hpp"

namespace raylib
{
    namespace model
    {
        class Mesh {
          public:
            Mesh(const Mesh &other);

            Mesh(const ::Mesh &mesh);

            ~Mesh();

            static Mesh genCube(float width, float height, float length);
            static Mesh genCube(const raylib::core::Vector3 &size);

            static Mesh genCubicMap(const raylib::textures::Image &image, float width, float height, float length);
            static Mesh genCubicMap(const raylib::textures::Image &image, const raylib::core::Vector3 &vector);

            /// Gets the C Raylib mutable version of the mesh
            ///
            /// @return The raylib version of the mesh
            ::Mesh const &asRaylib() const;

          private:
            ::Mesh _mesh;
        };
    } // namespace model
} // namespace raylib

#endif /* !RAYLIB_CORE_MESH_HPP_ */
