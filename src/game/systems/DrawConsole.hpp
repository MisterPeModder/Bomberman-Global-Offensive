/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Draw Console
*/

#ifndef GAME_SYSTEMS_DRAW_CONSOLE_HPP_
#define GAME_SYSTEMS_DRAW_CONSOLE_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    /// Updates the first selected input field found.
    ///
    /// Required storages: game::components::Positions, game::KeyboardInput
    struct DrawConsole : public ecs::System {
        /// Draw all the entities with the components Position and KeyboardInput.
        ///
        /// @param data view on the world.
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_DRAW_CONSOLE_HPP_ */
