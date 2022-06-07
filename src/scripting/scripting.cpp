/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** scripting
*/

#include <iostream>
#include <mujs.h>
#include <string_view>

extern "C"
{
    static void hello(js_State *state)
    {
        std::string_view name = js_tostring(state, 1);

        std::cout << "Hello, " << name << " from JS (through C++)" << std::endl;

        // return undefined to JS
        js_pushundefined(state);
    }
}

void scriptingHelloWorld()
{
    js_State *state = js_newstate(nullptr, nullptr, JS_STRICT);

    js_newcfunction(state, &hello, "hello", 1);
    js_setglobal(state, "hello");

    js_dostring(state, "hello('Mark');");

    js_freestate(state);
}
