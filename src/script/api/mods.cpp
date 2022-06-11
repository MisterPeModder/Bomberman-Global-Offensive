/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Common JS utilities
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
    auto engine = bmjs::Engine::rawInstance();
    auto mod = engine ? engine->getMod(static_cast<std::size_t>(modId)) : nullptr;

    if (!engine || !mod)
        return;
    mod->getLogger().log(Logger::Severity::Information, message);
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
