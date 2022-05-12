/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Localization
*/

#ifndef LOCALIZATION_LOCALIZATION_HPP_
#define LOCALIZATION_LOCALIZATION_HPP_

#include <map>
#include <vector>
#include "RessourceFile.hpp"
#include <string_view>

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

        /// Change the current locale used.
        /// @note Default locale is english @b "eg" .
        ///
        /// @param locale country code ("en", "fr"...)
        /// @throw ??? when the locale can't be loaded (no file found).
        static void setLocale(std::string_view locale);

        /// Load all the locales used by the project.
        /// @note All loaded locales will have new messages written in the corresponding file.
        ///
        /// @param locales list of country codes ("en", "fr"...)
        /// @param createNew whether or not the unfound files must be created.
        /// @throw ??? when a locale is not found and @c createNew is set to false.
        ///
        static void loadLocales(const std::vector<std::string_view> &locales, bool createNew = false);

        /// Translate a message in the current locale.
        /// @note @c registerNew will affect all loaded locales.
        /// @note If the translation is found but is empty, @c msg will be returned.
        ///
        /// @param msg message to translate.
        /// @param registerNew whether or not the message must be created if translation not found.
        /// @return std::string_view translated message.
        /// @throw ??? when the translation is not found and @c registerNew is set to false.
        ///
        static std::string_view translate(std::string_view msg, bool registerNew = true);

      private:
        Localization();

        static Localization _Instance;
        std::map<std::string, RessourceFile> _locales;
        std::string _locale;
        std::string _localesDirectory;
    };
} // namespace localization
#endif /* !LOCALIZATION_LOCALIZATION_HPP_ */
