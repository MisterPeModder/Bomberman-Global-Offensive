#ifndef GAME_COMPONENTS_MODEL_HPP_
#define GAME_COMPONENTS_MODEL_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/model/Model.hpp"
// #include "raylib/model/Mesh.hpp"

namespace game
{
    struct Model : public ecs::Component, public raylib::model::Model {
        Model(raylib::model::Model &pmodel) : raylib::model::Model(pmodel) {}
        // Model(const raylib::model::Mesh &pmesh) : raylib::model::Model(pmesh) {}
        Model(std::filesystem::path &path) : raylib::model::Model(path) {}
    };
} // namespace game

#endif
