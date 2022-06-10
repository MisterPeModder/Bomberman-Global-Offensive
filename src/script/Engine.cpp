/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Engine
*/

#include "script/Engine.hpp"
#include "script/api/api.hpp"
#include "util/util.hpp"

#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

namespace bmjs
{
    std::weak_ptr<Engine> Engine::_instance = std::weak_ptr<Engine>();

    std::shared_ptr<Engine> Engine::create()
    {
        if (Engine::_instance.expired()) {
            // using 'new' because Engine's constructor is private
            std::shared_ptr<Engine> newInstance(new Engine());
            Engine::_instance = newInstance;
            return newInstance;
        }
        return Engine::_instance.lock();
    }

    std::weak_ptr<Engine> Engine::instance() { return Engine::_instance; }

    void Engine::loadMod(std::string_view name)
    {
        auto modPath = util::makePath(std::filesystem::path("mods"), name);
        modPath += ".js";
        this->load(modPath);
    }

#ifdef __EMSCRIPTEN__
    Engine::Engine() { BMJS_USE_API(common); }

    Engine::~Engine() {}

    void Engine::load(std::filesystem::path const &path)
    {
        std::ifstream input(path);
        std::string content((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));

        emscripten_run_script(content.c_str());
    }

    void Engine::loadApi()
    {
        // The API is already preloaded on emscripten
    }
#else
    void registerMuJSBindings(js_State *state);

    Engine::Engine() : _state(js_newstate(nullptr, nullptr, JS_STRICT))
    {
        BMJS_USE_API(common);
        registerMuJSBindings(this->_state);
    }

    Engine::~Engine()
    {
        js_gc(this->_state, 0);
        js_freestate(this->_state);
    }

    void Engine::load(std::filesystem::path const &path) { js_dofile(this->_state, path.c_str()); }

    void Engine::loadApi()
    {
        auto apiPath = util::makePath(std::filesystem::path("mods"), "api.js");
        this->load(apiPath);
    }

#endif // !defined(__EMSCRIPTEN__)
} // namespace bmjs
