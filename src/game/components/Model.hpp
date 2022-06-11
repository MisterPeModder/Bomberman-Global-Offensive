#ifndef GAME_COMPONENTS_MODEL_HPP_
#define GAME_COMPONENTS_MODEL_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/model/Mesh.hpp"
#include "raylib/model/Model.hpp"

namespace game::components
{
    struct Model : public ecs::Component, public raylib::model::Model {
        Model(const raylib::model::Model &pModel) : raylib::model::Model(pModel) {}
        Model(const raylib::model::Mesh &pMesh) : raylib::model::Model(pMesh) {}
        Model(const std::filesystem::path &pPath) : raylib::model::Model(pPath) {}
    };
} // namespace game::components

#endif
