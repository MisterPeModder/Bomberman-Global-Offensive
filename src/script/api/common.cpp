/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Common JS utilities
*/

#include <iostream>
#include <string>
#include <unordered_map>

#include "logger/Logger.hpp"
#include "raylib/core/Window.hpp"
#include "script/JsException.hpp"
#include "script/script.hpp"

/// Source Engine styled CVARS. Just for testing, of course.
static std::unordered_map<std::string, bmjs::Number> cvars = std::unordered_map<std::string, bmjs::Number>();

BMJS_API_START(common)

BMJS_DEFINE bmjs::Number common_setCVar(bmjs::String name, bmjs::Number value)
{
    std::string key(name);
    auto it = cvars.find(name);
    bmjs::Number old = it == cvars.end() ? 0 : it->second;

    cvars[key] = value;
    Logger::logger.log(
        Logger::Severity::Information, [&](auto &out) { out << "cvar '" << name << "' set to " << value; });
    return old;
}

BMJS_DEFINE bmjs::Number common_getCVar(bmjs::String name)
{
    std::string key(name);
    auto it = cvars.find(name);

    return it == cvars.end() ? 0 : it->second;
}

BMJS_DEFINE void common_log(bmjs::String message) { Logger::logger.log(Logger::Severity::Information, message); }

BMJS_DEFINE void common_error(bmjs::String message) { Logger::logger.log(Logger::Severity::Error, message); }

BMJS_DEFINE void common_warn(bmjs::String message) { Logger::logger.log(Logger::Severity::Warning, message); }

BMJS_DEFINE void common_debug(bmjs::String message) { Logger::logger.log(Logger::Severity::Debug, message); }

BMJS_DEFINE void common_setWidth(bmjs::Number width)
{
    raylib::core::Window::setSize(static_cast<int>(width), raylib::core::Window::getHeight());
}

BMJS_DEFINE void common_setHeight(bmjs::Number height)
{
    raylib::core::Window::setSize(raylib::core::Window::getWidth(), static_cast<int>(height));
}

BMJS_DEFINE bmjs::Number common_getWidth() { return raylib::core::Window::getWidth(); }

BMJS_DEFINE bmjs::Number common_getHeight() { return raylib::core::Window::getHeight(); }

BMJS_API_END
