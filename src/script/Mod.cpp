/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Engine
*/

#include "script/Mod.hpp"
#include "logger/Logger.hpp"
#include "script/JsException.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>

namespace bmjs
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Instantiation
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Mod::Mod(std::size_t id, std::string_view name, std::string_view description)
        : _id(id), _name(name), _description(description), _logger(std::make_unique<Logger>())
    {
        std::string loggerName = "mods/";

        loggerName += name;
        _logger->setLogLevel(Logger::Severity::Information);
        _logger->setLogInfo(Logger::LogInfo::Time);
        _logger->setName(loggerName);
    }

    Mod::~Mod() { this->onUnload(); }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Properties
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Logger const &Mod::getLogger() const noexcept { return *this->_logger; }

    Logger &Mod::getLogger() noexcept { return *this->_logger; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Events
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Mod::setLoadCallback(std::optional<Function<void>> onLoad) { this->_onLoad = onLoad; }

    void Mod::setUnloadCallback(std::optional<Function<void>> onUnload) { this->_onUnload = onUnload; }

    void Mod::onLoad()
    {
        if (this->_onLoad) {
            try {
                (*this->_onLoad)();
            } catch (JsException const &error) {
                this->getLogger().log(
                    Logger::Severity::Error, [&](auto &out) { out << "Loading error: " << error.what(); });
            }
        }
    }

    void Mod::onUnload()
    {
        if (this->_onUnload) {
            try {
                (*this->_onUnload)();
            } catch (JsException const &error) {
                this->getLogger().log(
                    Logger::Severity::Error, [&](auto &out) { out << "Unloading error: " << error.what(); });
            }
        }
    }
} // namespace bmjs
