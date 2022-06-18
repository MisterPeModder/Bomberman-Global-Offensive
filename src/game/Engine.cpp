/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Engine
*/

#include "game/Engine.hpp"
#include "game/scenes/SplashScene.hpp"
#include "localization/Localization.hpp"
#include "raylib/core/Audio.hpp"
#include "raylib/core/Window.hpp"

#pragma region Browser Events
#ifdef __EMSCRIPTEN__

    #include <emscripten/emscripten.h>
    #include <emscripten/html5.h>

extern "C"
{
    /// Emscripten main loop callback
    static void Engine_drawFrame(void *userData)
    {
        game::Engine *engine = reinterpret_cast<game::Engine *>(userData);
        engine->drawFrame();
    }

    /// Emscripten window resize event
    static EM_BOOL Engine_onResize([[maybe_unused]] int eventType, [[maybe_unused]] EmscriptenUiEvent const *event,
        [[maybe_unused]] void *userData)
    {
        raylib::core::Vector2<double> newSize;

        if (emscripten_get_element_css_size("#emscripten_wrapper", &newSize.x, &newSize.y) == EMSCRIPTEN_RESULT_SUCCESS)
            raylib::core::Window::setSize(newSize.x - 32, newSize.y - 32);
        return EM_TRUE;
    }

    /// Emscriten fullscreen state change event
    static EM_BOOL Engine_onFullscreenChange(
        [[maybe_unused]] int eventType, EmscriptenFullscreenChangeEvent const *event, [[maybe_unused]] void *userData)
    {
        if (!event->isFullscreen) {
            raylib::core::Window::setSize(1, 1);
            Engine_onResize(EMSCRIPTEN_EVENT_FULLSCREENCHANGE, nullptr, nullptr);
        }
        return EM_FALSE;
    }
}

#endif // !defined(__EMSCRIPTEN__)
#pragma endregion Browser Events

namespace game
{
    Engine::Engine() : _debugMode(false)
    {
        _scene = std::make_unique<SplashScene>();
        _scene->getWorld().addResource<resources::EngineResource>(this);
        loadSettings();
    }

    game::IScene &Engine::getScene() { return *_scene; }

    const game::IScene &Engine::getScene() const { return *_scene; }

    void Engine::setDebugMode(bool value) noexcept { this->_debugMode = value; }

    bool Engine::getDebugMode() const noexcept { return this->_debugMode; }

    void Engine::switchScene()
    {
        if (_waitingScene) {
            _scene.swap(_waitingScene);
            _waitingScene.release();
        }
    }

    void Engine::run()
    {
#ifdef __EMSCRIPTEN__
        emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_FALSE, &Engine_onResize);
        Engine_onResize(EMSCRIPTEN_EVENT_RESIZE, nullptr, nullptr);

        emscripten_set_fullscreenchange_callback(
            EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_FALSE, &Engine_onFullscreenChange);

        // We cannot use the WindowShouldClose() loop on the web,
        // since there is no such thing as a window.
        emscripten_set_main_loop_arg(&Engine_drawFrame, reinterpret_cast<void *>(this), 0, 1);
#else
        while (!raylib::core::Window::getShouldClose())
            this->drawFrame();
#endif // !defined(__EMSCRIPTEN__)}
    }

    void Engine::drawFrame()
    {
        this->_scene->drawFrame();
        if (this->_debugMode)
            raylib::core::Window::drawFPS(10, 10);
        this->switchScene();
    }

    settings::Settings &Engine::getSettings() { return _settings; }

    const settings::Settings &Engine::getSettings() const { return _settings; }

    void Engine::loadSettings()
    {
        _settings.load();

        raylib::core::Audio::setMasterVolume(_settings.getMasterVolume());
        raylib::core::Window::setTargetFPS(_settings.getTargetFramerate());
        raylib::core::Window::setSize(_settings.getResolution().x, _settings.getResolution().y);
        if (raylib::core::Window::isFullscreen() != _settings.isFullscreen())
            raylib::core::Window::toggleFullscreen();
        localization::Localization::setLocale(_settings.getLocale());
    }

    Users &Engine::getUsers() { return _users; }

    const Users &Engine::getUsers() const { return _users; }

} // namespace game
