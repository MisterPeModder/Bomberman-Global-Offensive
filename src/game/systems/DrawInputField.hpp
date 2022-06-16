/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Draw Input Fields
*/

#ifndef GAME_SYSTEMS_DRAW_INPUT_FIELD_HPP_
#define GAME_SYSTEMS_DRAW_INPUT_FIELD_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    /// Updates the first selected input field found.
    ///
    /// Required storages: game::components::Positions, game::gui::InputField
    struct DrawInputField : public ecs::System {
        /// Draw all the entities with the components Position and InputField.
        ///
        /// @param data view on the world.
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_DRAW_INPUT_FIELD_HPP_ */
