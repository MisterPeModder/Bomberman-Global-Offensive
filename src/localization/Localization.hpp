/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Localization
*/

#ifndef LOCALIZATION_LOCALIZATION_HPP_
#define LOCALIZATION_LOCALIZATION_HPP_

#include <vector>
#include "RessourceFile.hpp"

#define _(...) localization::Localization::translate(__VA_ARGS__)

/// Namespace regrouping all the i18n related classes.
namespace localization
{
    /// Singleton class to manage locales in ressources.
    class Localization {
      public:
        /// Destroy the Localization object.
        ~Localization() = default;

        /// Set the Locales Directory.
        /// @note By default the directory is "./locales"
        ///
        /// @param directory locales files directory.
        static void setLocalesDirectory(std::string_view directory);

        /// Get the Locales Directory.
        /// @note By default the directory is "./locales"
        ///
        /// @return std::string_view locales files directory.
        static std::string_view getLocalesDirectory();

        /// Get the path of a locale file.
        ///
        /// @param locale locale id (country code).
        /// @return std::string locale file path.
        static std::string getLocalePath(std::string_view locale);

        /// @copydoc RessourceFile::loadLocale
        static void setLocale(std::string_view locale, bool createNew = false);

        /// Save the loaded locale files.
        /// @note @ref saveLocales() is called on the Localization instance destruction.
        static void saveLocales();

        /// Get the loaded locale object
        /// @note By default the locale is not set (empty).
        ///
        /// @return std::string_view
        ///
        static std::string_view getLocale();

        /// Load all the locales used by the project.
        /// @note All loaded locales will have new messages written in the corresponding file.
        ///
        /// @param locales list of country codes ("en", "fr"...)
        /// @param createNew whether or not the unfound files must be created.
        /// @throw RessourceFile::LocaleNotFoundError when a locale is not found and @c createNew is set to false.
        ///
        static void loadLocales(const std::vector<std::string_view> &locales, bool createNew = false);

        /// @copydoc RessourceFile::translate
        /// @note @c registerNew will affect all loaded locales.
        /// @note If no locale was set using @ref setLocale() @c msg will always be returned.
        static std::string_view translate(std::string_view msg, bool registerNew = false);

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
        std::map<std::string, RessourceFile> _locales;
        std::string _locale;
        std::string _localesDirectory;
    };
} // namespace localization
#endif /* !LOCALIZATION_LOCALIZATION_HPP_ */
