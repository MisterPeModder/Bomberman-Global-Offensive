#ifndef GAME_COMPONENTS_MODEL_HPP_
#define GAME_COMPONENTS_MODEL_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/model/Model.hpp"

namespace game
{
    namespace components
    {
        struct Model : public ecs::Component {
            raylib::model::Model model;

            Model(raylib::model::Model &pmodel) : model(pmodel) {}
            Model(std::filesystem::path &path) : model(path) {}
        };
    } // namespace components
} // namespace game

#endif
