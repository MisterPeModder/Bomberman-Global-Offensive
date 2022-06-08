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
        /// Mesh class
        class Mesh {
          public:
            /// Deleted default constructor
            Mesh() = delete;

            /// Deleted copy operator
            ///
            /// @param other the mesh to not copy
            Mesh &operator=(const Mesh &other) = delete;

            /// Mesh copy constructor
            ///
            /// @param other the mesh to copy
            Mesh(const Mesh &other);

            /// C Raylib mesh import constructor
            ///
            /// @param mesh the C Raylib mesh to import
            Mesh(const ::Mesh &mesh);

            /// Destructor
            ~Mesh();

            /// Generates a cubic mesh
            ///
            /// @param width the width of the cube
            /// @param height the height of the cube
            /// @param length the length of the cube
            ///
            /// @return The created cubic mesh
            static Mesh genCube(float width, float height, float length);

            /// Generates a cubic mesh
            ///
            /// @param size the size of the cube
            ///
            /// @return The created cubic mesh
            static Mesh genCube(const raylib::core::Vector3 &size);

            /// Generates a cubic map mesh from an image
            ///
            /// @param image the image used to generate the mesh
            /// @param width the width of the cube
            /// @param height the height of the cube
            /// @param length the length of the cube
            ///
            /// @return The created cubic mesh
            static Mesh genCubicMap(const raylib::textures::Image &image, float width, float height, float length);

            /// Generates a cubic map mesh from an image
            ///
            /// @param image the image used to generate the mesh
            /// @param size the size of the cube
            ///
            /// @return The created cubic mesh
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
