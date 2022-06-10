#ifndef GAME_COMPONENTS_MODEL_HPP_
#define GAME_COMPONENTS_MODEL_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/model/Model.hpp"

namespace game::components
{
    struct Model : public ecs::Component, public raylib::model::Model {
        Model(const raylib::model::Model &pmodel) : raylib::model::Model(pmodel) {}
        Model(const std::filesystem::path &path) : raylib::model::Model(path) {}
    };
} // namespace game::components

#endif
