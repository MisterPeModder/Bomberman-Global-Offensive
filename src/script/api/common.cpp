/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Common JS utilities
*/

#include <iostream>
#include <string>
#include <unordered_map>

#include "script/script.hpp"

/// Source Engine styled CVARS. Just for testing, of course.
static std::unordered_map<std::string, bmjs::Number> cvars = std::unordered_map<std::string, bmjs::Number>();

BMJS_API_START(common)

BMJS_DEFINE bmjs::Number bmjs_common_setCVar(bmjs::String name, bmjs::Number value)
{
    std::string key(name);
    auto it = cvars.find(name);
    bmjs::Number old = it == cvars.end() ? 0 : it->second;

    cvars[key] = value;
    std::cout << "cvar '" << name << "' set to " << value << std::endl;
    return old;
}

BMJS_DEFINE bmjs::Number bmjs_common_getCVar(bmjs::String name)
{
    std::string key(name);
    auto it = cvars.find(name);

    return it == cvars.end() ? 0 : it->second;
}

BMJS_DEFINE void bmjs_common_doNothing() {}

BMJS_DEFINE int bmjs_common_helloWorld()
{
    std::cout << "hello, world" << std::endl;
    return 42;
}

BMJS_API_END
