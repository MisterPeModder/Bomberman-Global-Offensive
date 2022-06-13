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
#include <string>
#include <utility>
#include <string_view>

namespace bmjs
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Instantiation
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Mod::Mod(std::size_t id, std::string_view name, std::string_view description)
        : _id(id), _name(name), _description(description), _loaded(false), _logger()
    {
        std::string loggerName = "mods/";

        loggerName += name;
        _logger.setLogLevel(Logger::Severity::Information);
        _logger.setLogInfo(Logger::LogInfo::Time);
        _logger.setName(loggerName);
    }

    Mod::Mod(Mod &&other)
        : _id(other._id), _name(std::move(other._name)), _description(std::move(other._description)),
          _loaded(other._loaded), _logger(std::move(other._logger)), _onLoad(std::move(other._onLoad)),
          _onUnload(std::move(other._onUnload))
    {
        other._loaded = false;
    }

    Mod::~Mod() { this->onUnload(); }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Properties
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Logger const &Mod::getLogger() const noexcept { return this->_logger; }

    Logger &Mod::getLogger() noexcept { return this->_logger; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Events
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Mod::setLoadCallback(std::optional<Function<void>> onLoad) { this->_onLoad = onLoad; }

    void Mod::setUnloadCallback(std::optional<Function<void>> onUnload) { this->_onUnload = onUnload; }

    void Mod::onLoad()
    {
        if (this->_loaded)
            return;
        this->_loaded = true;
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
        if (!this->_loaded)
            return;
        this->_loaded = false;
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
