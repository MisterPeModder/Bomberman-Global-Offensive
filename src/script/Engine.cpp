/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Engine
*/

#include "script/Engine.hpp"

#include "script/api/api.hpp"

namespace bmjs
{
#ifdef __EMSCRIPTEN__
    Engine::Engine() { BMJS_USE_API(common); }

    Engine::~Engine() {}
#else
    void registerMuJSBindings(js_State *state);

    Engine::Engine() : _state(js_newstate(nullptr, nullptr, JS_STRICT))
    {
        BMJS_USE_API(common);
        registerMuJSBindings(this->_state);
        js_dostring(this->_state, "setCVar(\"sv_cheats\", 1);");
    }

    Engine::~Engine()
    {
        js_gc(this->_state, 0);
        js_freestate(this->_state);
    }

#endif // !defined(__EMSCRIPTEN__)
} // namespace bmjs
