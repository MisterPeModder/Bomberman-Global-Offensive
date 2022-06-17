/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Engine
*/

#include "script/Engine.hpp"
#include "logger/Logger.hpp"
#include "script/JsException.hpp"
#include "script/api/api.hpp"
#include "util/util.hpp"

#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

#ifndef __EMSCRIPTEN__
extern "C"
{
    static void bmjs_Engine_panic(js_State *) { throw bmjs::JsException("JS engine panic"); }
    static void bmjs_Engine_report(js_State *, char const *message) { throw bmjs::JsException(message); }
}
#endif // !defined(__EMSCRIPTEN__)

namespace bmjs
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Instantiation
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::weak_ptr<Engine> Engine::_instance = std::weak_ptr<Engine>();

    Engine *Engine::_rawInstance = nullptr;

    std::shared_ptr<Engine> Engine::create(game::Engine *gameEngine)
    {
        if (Engine::_instance.expired()) {
            // using 'new' because Engine's constructor is private
            std::shared_ptr<Engine> newInstance(new Engine(gameEngine));
            Engine::_instance = newInstance;
            Engine::_rawInstance = newInstance.get();
            return newInstance;
        }
        return Engine::_instance.lock();
    }

    std::weak_ptr<Engine> Engine::instance() { return Engine::_instance; }

    Engine *Engine::rawInstance() { return Engine::_rawInstance; }

    Engine::~Engine()
    {
        this->_mods.clear();
        this->_delete();
        this->_rawInstance = nullptr;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Loading
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Engine::load(std::filesystem::path const &path)
    {
        Logger::logger.log(
            Logger::Severity::Information, [&](auto &out) { out << "Loading script at '" << path << "'"; });
        this->_load(path);
    }

    void Engine::loadScript(std::string_view name)
    {
        auto modPath = util::makePath("mods", name);
        modPath += ".js";
        this->load(modPath);
    }

    void Engine::loadApi() { this->_loadApi(); }

    std::string Engine::loadString(std::string_view toRun) { return this->_loadString(toRun); }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modding
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Mod &Engine::addMod(std::string_view name, std::string_view description)
    {
        return this->_mods.emplace_back(this->_mods.size(), name, description);
    }

    Mod const *Engine::getMod(std::size_t modId) const noexcept
    {
        if (modId >= this->_mods.size())
            return nullptr;
        return &*(this->_mods.cbegin() + modId);
    }

    Mod *Engine::getMod(std::size_t modId) noexcept
    {
        if (modId >= this->_mods.size())
            return nullptr;
        return &*(this->_mods.begin() + modId);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Game Access
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    game::Engine const &Engine::getGameEngine() const noexcept { return *this->_gameEngine; }

    game::Engine &Engine::getGameEngine() noexcept { return *this->_gameEngine; }

#ifdef __EMSCRIPTEN__
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Emscripten-Specific Magic
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Engine::Engine(game::Engine *gameEngine) : _gameEngine(gameEngine) { bmjs::useApis(); }

    void Engine::_load(std::filesystem::path const &path)
    {
        std::ifstream input(path);
        std::string content((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));

        emscripten_run_script(content.c_str());
    }

    void Engine::_loadApi()
    {
        // The API is already preloaded on emscripten
    }

    std::string Engine::_loadString(std::string_view toRun) { return emscripten_run_script_string(toRun.data()); }

    void Engine::_delete() {}
#else
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // MuJS-Specific Magic
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void registerMuJSBindings(js_State *state);

    Engine::Engine(game::Engine *gameEngine) : _gameEngine(gameEngine), _state(js_newstate(nullptr, nullptr, JS_STRICT))
    {
        js_atpanic(this->_state, &bmjs_Engine_panic);
        js_setreport(this->_state, &bmjs_Engine_report);
        bmjs::useApis();
        registerMuJSBindings(this->_state);
    }

    void Engine::_load(std::filesystem::path const &path)
    {
        std::string pathStr = path.generic_string();

        js_dofile(this->_state, pathStr.c_str());
    }

    void Engine::_loadApi()
    {
        auto apiPath = util::makePath("mods", "api.js");
        this->load(apiPath);
    }

    std::string Engine::_loadString(std::string_view toRun)
    {
        if (js_ploadstring(this->_state, "[console]", toRun.data())) {
            JsException error(js_trystring(this->_state, -1, "Error"));
            js_pop(this->_state, 1);
            throw error;
        }
        js_pushundefined(this->_state);
        if (js_pcall(this->_state, 0)) {
            JsException error(js_trystring(this->_state, -1, "Error"));
            js_pop(this->_state, 1);
            throw error;
        }
        if (js_isdefined(this->_state, -1)) {
            std::string result(js_trystring(this->_state, -1, "[no string representation]"));

            js_pop(this->_state, 1);
            return result;
        }
        js_pop(this->_state, 1);
        return "undefined";
    }

    void Engine::_delete()
    {
        js_gc(this->_state, 0);
        js_freestate(this->_state);
    }
#endif // !defined(__EMSCRIPTEN__)
} // namespace bmjs
