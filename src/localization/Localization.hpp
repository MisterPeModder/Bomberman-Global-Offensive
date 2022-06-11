/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Localization
*/

#ifndef LOCALIZATION_LOCALIZATION_HPP_
#define LOCALIZATION_LOCALIZATION_HPP_

#include <filesystem>
#include <vector>
#include "ResourceFile.hpp"

/// Namespace regrouping all the i18n related classes.
namespace localization
{
    /// Singleton class to manage locales in resources.
    class Localization {
      public:
        /// Destroy the Localization object.
        ~Localization() = default;

        /// Set the Locales Directory.
        /// @note By default the directory is "./locales"
        ///
        /// @param directory locales files directory.
        static void setLocalesDirectory(const std::filesystem::path &directory);

        /// Get the Locales Directory.
        /// @note By default the directory is "./locales"
        ///
        /// @return std::string_view locales files directory.
        static const std::filesystem::path &getLocalesDirectory();

        /// Get the path of a locale file.
        ///
        /// @param locale locale id (country code).
        /// @return std::filesystem::path locale file path.
        static std::filesystem::path getLocalePath(std::string_view locale);

        /// @copydoc ResourceFile::loadLocale
        static void setLocale(std::string_view locale);

        /// Save the loaded locale files.
        /// @note @ref saveLocales() is called on the Localization instance destruction.
        static void saveLocales();

        /// Get the loaded locale object
        /// @note By default the locale is not set (empty).
        ///
        /// @return std::string_view current locale.
        ///
        static std::string_view getLocale();

        /// Load all the locales used by the project.
        /// @note All loaded locales will have new messages written in the corresponding file.
        /// @note If the file can't be found in debug mode, it is created on save when new messages are registered.
        ///
        /// @param locales list of country codes ("en", "fr"...)
        /// @throw ResourceFile::LocaleNotFoundError when a locale is not found in release mode.
        ///
        static void loadLocales(const std::vector<std::string_view> &locales);

        /// @copydoc ResourceFile::translate
        /// @note If no locale was set using @ref setLocale() @c msg will always be returned.
        static std::string_view translate(std::string_view msg);

        /// Register a new string in the loaded locales.
        /// @note If the string is already set, does nothing.
        /// @note The string will be added at the end of the files on save.
        ///
        /// @param msg message id.
        static void registerString(std::string_view msg);

      private:
        /// Construct a new Localization object.
        /// @note The default locale is empty.
        Localization();

        static Localization _Instance;
        std::map<std::string, ResourceFile> _locales;
        std::string _locale;
        std::filesystem::path _localesDirectory;
    };
} // namespace localization
#endif /* !LOCALIZATION_LOCALIZATION_HPP_ */
