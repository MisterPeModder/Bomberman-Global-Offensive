#ifndef GAME_COMPONENTS_MODEL_HPP_
#define GAME_COMPONENTS_MODEL_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/model/Model.hpp"

namespace game
{
    namespace components
    {
        struct Model : public ecs::Component, public raylib::model::Model {
            Model(raylib::model::Model &pmodel) : raylib::model::Model(pmodel) {}
            Model(std::filesystem::path &path) : raylib::model::Model(path) {}
        };
    } // namespace components
} // namespace game

#endif
