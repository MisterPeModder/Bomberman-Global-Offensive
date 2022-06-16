/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** DrawText
*/

#ifndef GAME_SYSTEMS_UPDATE_INPUT_FIELDS_HPP_
#define GAME_SYSTEMS_UPDATE_INPUT_FIELDS_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    /// Updates the first selected input field found.
    ///
    /// Required resources: ecs::Timer
    /// Required storages: game::gui::InputField
    struct UpdateInputFields : public ecs::System {
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_UPDATE_INPUT_FIELDS_HPP_ */
