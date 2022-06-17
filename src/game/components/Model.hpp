/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** Model
*/

#ifndef GAME_COMPONENTS_MODEL_HPP_
#define GAME_COMPONENTS_MODEL_HPP_

#include <filesystem>
#include "Reference.hpp"
#include "ecs/Component.hpp"
#include "raylib/model/Mesh.hpp"
#include "raylib/model/Model.hpp"

namespace game::components
{
    struct Model : public ecs::Component, public raylib::model::Model {
        Model(const raylib::model::Model &pModel) : raylib::model::Model(pModel) {}
        Model(const raylib::model::Mesh &pMesh) : raylib::model::Model(pMesh) {}
        Model(const raylib::model::Mesh &pMesh, const raylib::textures::Texture2D &texture, int materialId, int mapType) : raylib::model::Model(pMesh, texture, materialId, mapType) {}
        Model(const raylib::model::Mesh &pMesh, bool ownsMesh = true) : raylib::model::Model(pMesh, ownsMesh) {}
        Model(const std::filesystem::path &pPath) : raylib::model::Model(pPath) {}
    };

    using ModelReference = Reference<raylib::model::Model>;
} // namespace game::components

#endif
