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
#include "raylib/core/scoped.hpp"
#include "raylib/shaders/Shader.hpp"
#include "util/util.hpp"

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
    static EM_BOOL Engine_onResize(
        [[maybe_unused]] int eventType, [[maybe_unused]] EmscriptenUiEvent const *event, void *userData)
    {
        game::Engine *engine = reinterpret_cast<game::Engine *>(userData);
        raylib::core::Vector2<double> newSize;

        if (emscripten_get_element_css_size("#emscripten_wrapper", &newSize.x, &newSize.y)
            == EMSCRIPTEN_RESULT_SUCCESS) {
            newSize -= raylib::core::Vector2<double>(32.0, 32.0);
            raylib::core::Window::setSize(newSize.x, newSize.y);
            engine->getSettings().setResolution(static_cast<raylib::core::Vector2i>(newSize));
            engine->updateRenderTarget();
        }
        return EM_TRUE;
    }

    /// Emscripten fullscreen state change event
    static EM_BOOL Engine_onFullscreenChange(
        [[maybe_unused]] int eventType, EmscriptenFullscreenChangeEvent const *event, void *userData)
    {
        game::Engine *engine = reinterpret_cast<game::Engine *>(userData);
        raylib::core::Vector2<double> newSize;

        if (!event->isFullscreen) {
            raylib::core::Window::setSize(1, 1);
            Engine_onResize(EMSCRIPTEN_EVENT_FULLSCREENCHANGE, nullptr, userData);
        } else if (emscripten_get_element_css_size("#canvas", &newSize.x, &newSize.y) == EMSCRIPTEN_RESULT_SUCCESS) {
            raylib::core::Window::setSize(newSize.x, newSize.y);
            engine->getSettings().setResolution(static_cast<raylib::core::Vector2i>(newSize));
            engine->updateRenderTarget();
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
#ifdef __EMSCRIPTEN__
        // Setup emscripten events
        void *self = reinterpret_cast<void *>(this);
        emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, self, EM_FALSE, &Engine_onResize);
        emscripten_set_fullscreenchange_callback(
            EMSCRIPTEN_EVENT_TARGET_WINDOW, self, EM_FALSE, &Engine_onFullscreenChange);
#endif // !defined(__EMSCRIPTEN__)

        loadSettings();
        _scene = std::make_unique<SplashScene>();
        _scene->getWorld().addResource<resources::EngineResource>(this);
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
        // We cannot use the WindowShouldClose() loop on the web,
        // since there is no such thing as a window.
        emscripten_set_main_loop_arg(&Engine_drawFrame, reinterpret_cast<void *>(this), 0, 1);
#else
        while (!raylib::core::Window::shouldClose())
            this->drawFrame();
#endif // !defined(__EMSCRIPTEN__)}
    }

    void Engine::drawFrame()
    {
        this->_scene->drawFrame();
        {
            raylib::core::scoped::Drawing drawing;
            raylib::core::Window::clear();
            if (_globalShader) {
                raylib::core::scoped::Shader modeShader(*_globalShader.get());
                _renderTarget->drawYFlipped();
            } else
                _renderTarget->drawYFlipped();
        }
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
        this->setResolution(this->_settings.getResolution());
    }

    void Engine::updateRenderTarget(int width, int height)
    {
        _renderTarget = std::make_unique<raylib::textures::RenderTexture2D>(width, height);
    }

    const raylib::textures::RenderTexture2D &Engine::getRenderTarget() const { return *_renderTarget.get(); }

    void Engine::removeGlobalShader() { _globalShader.reset(); }

    void Engine::setGlobalShader(std::filesystem::path vertex, std::filesystem::path fragments,
        std::function<void(raylib::shaders::Shader &)> shaderSetup)
    {
        _globalShader = std::make_unique<raylib::shaders::Shader>(vertex, fragments);

        shaderSetup(*_globalShader.get());
    }

    const std::unique_ptr<raylib::shaders::Shader> &Engine::getGlobalShader() const { return _globalShader; }

    std::unique_ptr<raylib::shaders::Shader> &Engine::getGlobalShader() { return _globalShader; }

    void Engine::setColorBlindShader(int mode)
    {
        setGlobalShader(raylib::shaders::Shader::getPath("base_lighting.vs"),
            raylib::shaders::Shader::getPath("colorblind.fs"), [&mode](raylib::shaders::Shader &shader) {
                shader.bindLocations(SHADER_LOC_MATRIX_MODEL, "matModel");
                shader.setValue("mode", mode);
                shader.setValue("intensity", 1.f);
            });
    }

    void Engine::setResolution([[maybe_unused]] raylib::core::Vector2i resolution)
    {
#ifdef __EMSCRIPTEN__
        Engine_onResize(EMSCRIPTEN_EVENT_RESIZE, nullptr, reinterpret_cast<void *>(this));
#else
        raylib::core::Window::setSize(resolution.x, resolution.y);
        this->_settings.setResolution(resolution);
        this->updateRenderTarget(resolution.x, resolution.y);
#endif
    }
} // namespace game
