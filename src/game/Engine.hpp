/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Engine
*/

#ifndef GAME_ENGINE_HPP_
#define GAME_ENGINE_HPP_

#include <concepts>
#include <functional>
#include <memory>
#include "game/resources/Engine.hpp"
#include "game/scenes/IScene.hpp"

#include "raylib/shaders/Shader.hpp"
#include "raylib/textures/RenderTexture2D.hpp"

#include <iostream>

#include "Users.hpp"
#include "settings/Settings.hpp"

#include "raylib/core/Music.hpp"

namespace game
{
    class Engine {
      public:
        enum PreloadedMusics {
            MAIN_MENU_THEME,
            GAME_THEME,
        };

        /// Constructor
        Engine();

        /// Destructor
        ~Engine();

        /// Sets the active scene and deletes the old one
        template <std::derived_from<IScene> S, typename... Args> void setScene(Args &&...args)
        {
            _waitingScene = std::make_unique<S>(args...);
            _waitingScene->getWorld().addResource<resources::EngineResource>(this);
            _waitingScene->setupWorld();
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

        /// Gets the users (mutable)
        Users &getUsers();

        /// Gets the users (immutable)
        const Users &getUsers() const;
        /// Update the size of the render target to match the given parameters.
        ///
        /// @param width Render target width.
        /// @param heigth Render target width.
        void updateRenderTarget(
            int width = raylib::core::Window::getWidth(), int height = raylib::core::Window::getHeight());

        /// Get the Render Target.
        ///
        /// @return const raylib::textures::RenderTexture2D& engine render target.
        const raylib::textures::RenderTexture2D &getRenderTarget() const;

        /// Remove the currently loaded global shader.
        /// @note If no global shader is loaded, does nothing.
        void removeGlobalShader();

        /// Set the Global Shader.
        ///
        /// @param vertex vertex file (.vs).
        /// @param fragments fragments file (.fs)
        /// @param shaderSetup callback to setup the shader parameters.( @ref raylib::shaders::Shader::setValue() )
        void setGlobalShader(std::filesystem::path vertex, std::filesystem::path fragments,
            std::function<void(raylib::shaders::Shader &)> shaderSetup);

        /// Get the Global Shader.
        ///
        /// @return const std::unique_ptr<raylib::shaders::Shader>& global shader.
        const std::unique_ptr<raylib::shaders::Shader> &getGlobalShader() const;

        /// Get the Global Shader.
        ///
        /// @return std::unique_ptr<raylib::shaders::Shader>& global shader.
        std::unique_ptr<raylib::shaders::Shader> &getGlobalShader();

        /// Set the Color Blind shader.
        ///
        /// @param mode colorblind mode (in order [0, 2] Protanopia, Deuteranopia, Tritanopia)
        /// @todo Create an enum in an appropriate file.
        void setColorBlindShader(int mode = 2);

        /// Updates the game engine's render resolution.
        ///
        /// @param resolution The resolution.
        void setResolution(raylib::core::Vector2i resolution);

        /// Sets the game engine's current music.
        ///
        /// @param music The music.
        void setCurrentMusic(PreloadedMusics music);

        /// Resume current music
        void resumeCurrentMusic();

        /// Pause current music
        void pauseCurrentMusic();

        /// Update all music streams
        void updateMusicStreams();

      private:
        /// Load the settings from the settings file
        void loadSettings();

        /// Sets the active scene and deletes the old one
        std::unique_ptr<game::IScene> _scene;
        std::unique_ptr<game::IScene> _waitingScene;
        settings::Settings _settings;
        Users _users;
        std::unique_ptr<raylib::textures::RenderTexture2D> _renderTarget;
        std::unique_ptr<raylib::shaders::Shader> _globalShader;

        PreloadedMusics _currentMusic;
        raylib::core::Music _mainMenuTheme;
        raylib::core::Music _gameTheme;

        bool _debugMode;
    };
} // namespace game

#endif /* !ENGINE_HPP_ */
