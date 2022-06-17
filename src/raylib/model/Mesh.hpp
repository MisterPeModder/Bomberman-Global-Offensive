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

namespace raylib::model
{
    /// Mesh class
    class Mesh {
      public:
        /// Deleted default constructor
        /// @note Deleted because it would try to unload an invalid mesh on destruction.
        Mesh() = delete;

        /// C Raylib mesh import constructor
        ///
        /// @param mesh the C Raylib mesh to import
        Mesh(const ::Mesh &mesh);

        /// Generates a cubic mesh
        ///
        /// @param width the width of the cube
        /// @param height the height of the cube
        /// @param length the length of the cube
        ///
        /// @return The created cubic mesh
        Mesh(float width, float height, float length);

        /// Generates a cubic mesh
        ///
        /// @param size the size of the cube
        ///
        /// @return The created cubic mesh
        Mesh(const raylib::core::Vector3f &size);

        /// Generates a cubic map mesh from an image
        ///
        /// @param image the image used to generate the mesh
        /// @param width the width of the cube
        /// @param height the height of the cube
        /// @param length the length of the cube
        ///
        /// @return The created cubic mesh
        Mesh(const raylib::textures::Image &image, float width, float height, float length);

        /// Generates a cubic map mesh from an image
        ///
        /// @param image the image used to generate the mesh
        /// @param size the size of the cube
        ///
        /// @return The created cubic mesh
        Mesh(const raylib::textures::Image &image, const raylib::core::Vector3f &vector);

        /// Mesh copy constructor
        /// @note Deleted because it would cause double unload.
        Mesh(const Mesh &other) = delete;

        /// Deleted copy operator
        /// @note Deleted because it would cause double unload.
        Mesh &operator=(const Mesh &other) = delete;

        /// Destructor
        /// @warning Unload the mesh.
        ~Mesh();

        /// Gets the C Raylib immutable version of the mesh
        ///
        /// @return The raylib version of the mesh
        ::Mesh const &asRaylib() const;

        /// Gets the C Raylib mutable version of the mesh
        ///
        /// @return The raylib version of the mesh
        ::Mesh &asRaylib();

      private:
        ::Mesh _mesh;
    };
} // namespace raylib::model

#endif /* !RAYLIB_CORE_MESH_HPP_ */
