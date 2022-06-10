/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** DrawText
*/

#ifndef GAME_SYSTEMS_DRAWTEXT_HPP_
#define GAME_SYSTEMS_DRAWTEXT_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    /// Draw text system.
    struct DrawText : public ecs::System {
        /// Draw all the entities with the components Position and Textual.
        ///
        /// @param data view on the world.
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_DRAWTEXT_HPP_ */
