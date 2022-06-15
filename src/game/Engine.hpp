/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Engine
*/

#ifndef GAME_ENGINE_HPP_
#define GAME_ENGINE_HPP_

#include <concepts>
#include <memory>
#include "game/resources/Engine.hpp"
#include "game/scenes/IScene.hpp"

#include <iostream>

namespace game
{
    class Engine {
      public:
        /// Constructor
        Engine();

        /// Sets the active scene and deletes the old one
        template <std::derived_from<IScene> S> void setScene()
        {
            _waitingScene = std::make_unique<S>();
            _waitingScene->getWorld().addResource<resources::EngineResource>(this);
        }

        /// Gets the mutable active scene
        game::IScene &getScene();

        /// Gets the immutable active scene
        const game::IScene &getScene() const;

        /// Runs the game
        void run();

        void switchScene()
        {
            if (_waitingScene) {
                _scene.swap(_waitingScene);
                _waitingScene.release();
            }
        }

      private:
        /// Sets the active scene and deletes the old one
        std::unique_ptr<game::IScene> _scene;
        std::unique_ptr<game::IScene> _waitingScene;
    };
} // namespace game

#endif /* !ENGINE_HPP_ */
