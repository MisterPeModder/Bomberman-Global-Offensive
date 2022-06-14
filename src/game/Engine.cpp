/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Engine
*/

#include "game/Engine.hpp"
#include "game/scenes/GameScene.hpp"
#include "raylib/core/Window.hpp"

#pragma region Browser Events
#ifdef __EMSCRIPTEN__

    #include <emscripten/emscripten.h>
    #include <emscripten/html5.h>

extern "C"
{
    /// Emscripten main loop callback
    static void Game_drawFrame(void *userData)
    {
        game::Engine *engine = reinterpret_cast<game::Engine *>(userData);
        engine->getScene().getWorld();
        engine->getScene().drawFrame();
    }

    /// Emscripten window resize event
    static EM_BOOL Game_onResize([[maybe_unused]] int eventType, [[maybe_unused]] EmscriptenUiEvent const *event,
        [[maybe_unused]] void *userData)
    {
        raylib::core::Vector2<double> newSize;

        if (emscripten_get_element_css_size("#emscripten_wrapper", &newSize.x, &newSize.y) == EMSCRIPTEN_RESULT_SUCCESS)
            raylib::core::Window::setSize(newSize.x - 32, newSize.y - 32);
        return EM_TRUE;
    }

    /// Emscriten fullscreen state change event
    static EM_BOOL Game_onFullscreenChange(
        [[maybe_unused]] int eventType, EmscriptenFullscreenChangeEvent const *event, [[maybe_unused]] void *userData)
    {
        if (!event->isFullscreen) {
            raylib::core::Window::setSize(1, 1);
            Game_onResize(EMSCRIPTEN_EVENT_FULLSCREENCHANGE, nullptr, nullptr);
        }
        return EM_FALSE;
    }
}

#endif // !defined(__EMSCRIPTEN__)
#pragma endregion Browser Events

namespace game
{
    Engine::Engine()
    {
        std::cout << "eeee" << std::endl;
        setScene<game::GameScene>();
    }

    game::IScene &Engine::getScene() { return *_scene; }

    const game::IScene &Engine::getScene() const { return *_scene; }

    void Engine::run()
    {
#ifdef __EMSCRIPTEN__
        emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_FALSE, &Game_onResize);
        Game_onResize(EMSCRIPTEN_EVENT_RESIZE, nullptr, nullptr);

        emscripten_set_fullscreenchange_callback(
            EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_FALSE, &Game_onFullscreenChange);

        // We cannot use the WindowShouldClose() loop on the web,
        // since there is no such thing as a window.
        emscripten_set_main_loop_arg(&Game_drawFrame, reinterpret_cast<void *>(this), 0, 1);
#else
        while (!raylib::core::Window::shouldClose())
            _scene->drawFrame();
#endif // !defined(__EMSCRIPTEN__)}
    }
} // namespace game
