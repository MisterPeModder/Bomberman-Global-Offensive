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
        Mesh::Mesh(const Mesh &other) : _mesh(other._mesh) {}

        Mesh::Mesh(const ::Mesh &mesh) : _mesh(mesh) {}

        Mesh::~Mesh() {}

        Mesh Mesh::genCube(float width, float height, float length) { return Mesh(GenMeshCube(width, height, length)); }

        Mesh Mesh::genCube(const raylib::core::Vector3f &size) { return Mesh(GenMeshCube(size.x, size.y, size.z)); }

        Mesh genCubicMap(const raylib::textures::Image &image, float width, float height, float length)
        {
            return Mesh(GenMeshCubicmap(image.asRaylib(), {.x = width, .y = height, .z = length}));
        }

        Mesh genCubicMap(const raylib::textures::Image &image, const raylib::core::Vector3f &vector)
        {
            return Mesh(GenMeshCubicmap(image.asRaylib(), vector.asRaylib()));
        }

        ::Mesh const &Mesh::asRaylib() const { return _mesh; }
    } // namespace model
} // namespace raylib
