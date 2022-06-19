/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** JS Mod Object Methods
*/

/// @file
/// @internal
///
/// See api.js for documentation.

#include <iostream>
#include <string>

#include "logger/Logger.hpp"
#include "script/Engine.hpp"
#include "script/JsException.hpp"
#include "script/script.hpp"

namespace bmjs::mods
{
    static void log(Logger::Severity severity, bmjs::Number modId, bmjs::String message)
    {
        auto engine = bmjs::Engine::rawInstance();
        auto mod = engine ? engine->getMod(static_cast<std::size_t>(modId)) : nullptr;

        if (!engine || !mod)
            return;
        mod->getLogger().log(severity, message);
    }
} // namespace bmjs::mods

BMJS_API_START(mods)

BMJS_DEFINE bmjs::Number mods_create(bmjs::String name, bmjs::String description)
{
    auto engine = bmjs::Engine::instance().lock();

    if (!engine)
        return -1;
    return engine->addMod(name, description).getId();
}

BMJS_DEFINE void mods_enable(bmjs::Number modId)
{
    auto engine = bmjs::Engine::instance().lock();
    auto mod = engine ? engine->getMod(static_cast<std::size_t>(modId)) : nullptr;

    if (!engine || !mod)
        return;
    mod->onLoad();
    mod->getLogger().log(Logger::Severity::Information, "Loaded");
}

BMJS_DEFINE void mods_log(bmjs::Number modId, bmjs::String message)
{
    bmjs::mods::log(Logger::Severity::Information, modId, message);
}

BMJS_DEFINE void mods_error(bmjs::Number modId, bmjs::String message)
{
    bmjs::mods::log(Logger::Severity::Error, modId, message);
}

BMJS_DEFINE void mods_warn(bmjs::Number modId, bmjs::String message)
{
    bmjs::mods::log(Logger::Severity::Warning, modId, message);
}

BMJS_DEFINE void mods_debug(bmjs::Number modId, bmjs::String message)
{
    bmjs::mods::log(Logger::Severity::Debug, modId, message);
}

BMJS_DEFINE void mods_setLoadCallback(bmjs::Number modId, bmjs::Function<void> onLoad)
{
    auto engine = bmjs::Engine::instance().lock();
    auto mod = engine ? engine->getMod(static_cast<std::size_t>(modId)) : nullptr;

    if (!engine || !mod)
        return;
    mod->setLoadCallback(onLoad);
}

BMJS_DEFINE void mods_setUnloadCallback(bmjs::Number modId, bmjs::Function<void> onUnload)
{
    auto engine = bmjs::Engine::instance().lock();
    auto mod = engine ? engine->getMod(static_cast<std::size_t>(modId)) : nullptr;

    if (!engine || !mod)
        return;
    mod->setUnloadCallback(onUnload);
}

BMJS_API_END
