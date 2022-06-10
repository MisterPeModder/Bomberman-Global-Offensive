/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Engine
*/

/// @file
///
/// A JS game mod.

#ifndef SCRIPT_MOD_HPP__
#define SCRIPT_MOD_HPP__

#include "logger/Logger.hpp"
#include "script/script.hpp"

#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

namespace bmjs
{
    /// A JavaScript game mod instance.
    class Mod {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Instantiation
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// @param id The unique identifier of the mod.
        /// @param name The mod's name.
        /// @param description The mod's name.
        Mod(std::size_t id, std::string_view name, std::string_view description);

        /// Move constructor.
        Mod(Mod &&) = default;

        /// Cannot copy instances of Mod.
        Mod(Mod const &) = delete;

        ~Mod();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Properties
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// @returns The mod's ID.
        constexpr std::size_t getId() const noexcept { return this->_id; }

        /// @returns The mod's name.
        constexpr std::string const &getName() const noexcept { return this->_name; }

        /// @returns The mod's description.
        constexpr std::string const &getDescription() const noexcept { return this->_description; }

        /// @returns The mod's logger.
        Logger const &getLogger() const noexcept;

        /// @returns The mod's logger.
        Logger &getLogger() noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Events
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// Sets the callback used by onLoad().
        ///
        /// @param onLoad The callback.
        void setLoadCallback(std::optional<Function<void>> onLoad);

        /// Sets the callback used by onUnload().
        ///
        /// @param onUnload The callback.
        void setUnloadCallback(std::optional<Function<void>> onUnload);

        /// Called by scripts when a mod is fully initialized.
        void onLoad();

        /// Called by the Mod's destructor from C++.
        void onUnload();

      private:
        std::size_t _id;
        std::string _name;
        std::string _description;

        std::unique_ptr<Logger> _logger;

        std::optional<Function<void>> _onLoad;
        std::optional<Function<void>> _onUnload;
    };
} // namespace bmjs

#endif // !defined(SCRIPT_MOD_HPP__)
