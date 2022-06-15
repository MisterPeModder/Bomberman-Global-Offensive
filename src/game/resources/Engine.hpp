/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Map
*/

#ifndef GAME_RESOURCES_ENGINE_HPP_
#define GAME_RESOURCES_ENGINE_HPP_

#include "ecs/resource/Resource.hpp"

namespace game
{
    class Engine;
}

namespace game::resources
{
    /// Game engine resource.
    struct EngineResource : public ecs::Resource {
        /// Pointer to the engine.
        ///
        /// The game::Engine instance is allocated at the beginning of the game and lives for the whole lifetime of the
        /// program.
        ///
        /// It needs to be allocated on the heap by itself, since it is passed as the parameter of
        /// emscriptem_set_main_loop_arg.
        game::Engine *engine;

        /// Construct a new Engine resource.
        ///
        /// @param pEngine @ref engine.
        explicit EngineResource(game::Engine *pEngine) : engine(pEngine) {}
    };
} // namespace game::resources

#endif /* !GAME_RESOURCES_ENGINE_HPP_ */
