/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Generated File
*/

/// @file
/// @internal
///
/// MuJS Bindings generated by 'generate_bindings.py'
/// DO NOT EDIT!
///
/// Available groups:
/// - common (4 functions)

#ifndef __EMSCRIPTEN__
    #include "script/script.hpp"

extern "C"
{
    bmjs::Number bmjs_common_setCVar(bmjs::String name, bmjs::Number value);
    bmjs::Number bmjs_common_getCVar(bmjs::String name);
    void bmjs_common_doNothing();
    int bmjs_common_helloWorld();
}

extern "C"
{
    static void bmjs_common_setCVar_mujs(js_State *state)
    {
        bmjs::String name = js_tostring(state, 1);
        bmjs::Number value = js_tonumber(state, 2);

        bmjs::Number result = ::bmjs_common_setCVar(name, value);
        js_pushnumber(state, result);
    }

    static void bmjs_common_getCVar_mujs(js_State *state)
    {
        bmjs::String name = js_tostring(state, 1);

        bmjs::Number result = ::bmjs_common_getCVar(name);
        js_pushnumber(state, result);
    }

    static void bmjs_common_doNothing_mujs(js_State *state)
    {
        ::bmjs_common_doNothing();
        js_pushundefined(state);
    }

    static void bmjs_common_helloWorld_mujs(js_State *state)
    {
        int result = ::bmjs_common_helloWorld();
    }
}

namespace bmjs
{
    void registerMuJSBindings(js_State *state)
    {
        // register all bound functions as globals

        js_newcfunction(state, &::bmjs_common_setCVar_mujs, "bmjs_common_setCVar", 2);
        js_setglobal(state, "bmjs_common_setCVar");

        js_newcfunction(state, &::bmjs_common_getCVar_mujs, "bmjs_common_getCVar", 1);
        js_setglobal(state, "bmjs_common_getCVar");

        js_newcfunction(state, &::bmjs_common_doNothing_mujs, "bmjs_common_doNothing", 0);
        js_setglobal(state, "bmjs_common_doNothing");

        js_newcfunction(state, &::bmjs_common_helloWorld_mujs, "bmjs_common_helloWorld", 0);
        js_setglobal(state, "bmjs_common_helloWorld");
    }
} // namespace bmjs

#endif // !defined(__EMSCRIPTEN__)
