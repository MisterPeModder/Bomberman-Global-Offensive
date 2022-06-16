/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Mesh
*/

#include "Mesh.hpp"

namespace raylib
{
    namespace model
    {
        Mesh::Mesh(const ::Mesh &mesh) : _mesh(mesh) {}

        Mesh::Mesh(float width, float height, float length) { _mesh = GenMeshCube(width, height, length); }

        Mesh::Mesh(const raylib::core::Vector3f &size) { _mesh = GenMeshCube(size.x, size.y, size.z); }

        Mesh::Mesh(const raylib::textures::Image &image, float width, float height, float length)
        {
            _mesh = GenMeshCubicmap(image.asRaylib(), {.x = width, .y = height, .z = length});
        }

        Mesh::Mesh(const raylib::textures::Image &image, const raylib::core::Vector3f &vector)
        {
            _mesh = GenMeshCubicmap(image.asRaylib(), vector.asRaylib());
        }

        Mesh::~Mesh() { UnloadMesh(_mesh); }

        ::Mesh const &Mesh::asRaylib() const { return _mesh; }
        ::Mesh &Mesh::asRaylib() { return _mesh; }
    } // namespace model
} // namespace raylib
