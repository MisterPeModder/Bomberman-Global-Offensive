#ifndef GAME_COMPONENTS_MODEL_HPP_
#define GAME_COMPONENTS_MODEL_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/model/Model.hpp"

namespace game
{
    struct Model : public ecs::Component {
        raylib::model::Model &model;
        Model(raylib::model::Model &pmodel) : model(pmodel) {}
    };
} // namespace game

#endif
