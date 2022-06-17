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

#include "settings/Settings.hpp"

namespace game
{
    class Engine {
      public:
        /// Constructor
        Engine();

        /// Destructor
        ~Engine();

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

        /// Enables/disables the debug mode.
        ///
        /// When enabled, extra information will be displayed on screen, such as the game FPS counter.
        ///
        /// @param value @c true to enable, @c false to disable.
        void setDebugMode(bool value) noexcept;

        /// @see Engine::setDebugMode()
        ///
        /// @returns Whether the debug mode is enabled.
        bool getDebugMode() const noexcept;

        /// Switch to the waiting scene if it exists and releases the current one
        void switchScene();

        /// Runs the game
        void run();

        /// Called on each render tick.
        void drawFrame();

        /// Gets the settings (mutable)
        settings::Settings &getSettings();

        /// Gets the settings (immutable)
        const settings::Settings &getSettings() const;

      private:
        /// Load the settings from the settings file
        void loadSettings();

        /// Sets the active scene and deletes the old one
        std::unique_ptr<game::IScene> _scene;
        std::unique_ptr<game::IScene> _waitingScene;
        settings::Settings _settings;

        bool _debugMode;
    };
} // namespace game

#endif /* !ENGINE_HPP_ */
