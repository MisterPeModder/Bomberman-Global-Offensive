/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** RessourceFile
*/

#ifndef LOCALIZATION_RESSOURCEFILE_HPP_
#define LOCALIZATION_RESSOURCEFILE_HPP_

#include <map>
#include <stdexcept>
#include <string_view>

namespace localization
{
    /// File regrouping multiple @ref RessourceString in the same locale.
    class RessourceFile {
      public:
        /// Exception thrown when the locale file can't be found.
        class LocaleNotFoundError : public std::runtime_error {
          public:
            /// Construct a new LocaleNotFoundError object
            ///
            /// @param locale locale file searched.
            LocaleNotFoundError(std::string_view locale);
        };

        /// Exception thrown when a message in a locale can't be found.
        class MessageNotFoundError : public std::runtime_error {
          public:
            /// Construct a new MessageNotFoundError object
            ///
            /// @param locale locale specified searched.
            /// @param message message message to be translated.
            MessageNotFoundError(std::string_view locale, std::string_view message);
        };

        /// Construct a new Ressource File object. The object is invalid until a successfull call to @ref
        /// loadLocale() is made.
        RessourceFile() = default;

        /// Construct a new Ressource File object with a given locale.
        /// @note The file will be searched in the path given by @ref Localization::getLocalesDirectory().
        ///
        /// @param locale locale to load.
        RessourceFile(std::string_view locale);

        /// Destroy the Ressource File object.
        /// @note call @ref save().
        ~RessourceFile() = default;

        /// Load a locale file.
        ///
        /// @param locale country code ("en", "fr"...)
        /// @param createNew whether or not the file must be created if not found.
        /// @throw LocaleNotFoundError when the locale can't be found and @c createNew is set to false.
        void loadLocale(std::string_view locale, bool createNew = false);

        /// Save the locale file.
        /// @note @ref save() is called when the file is destroyed.
        void save();

        /// Get the loaded locale.
        /// @warning If no locale is set, an empty string is returned.
        ///
        /// @return std::string_view loaded locale.
        std::string_view getLocale() const;

        /// Translate a message in the loaded locale.
        /// @note If the translation is found but is empty, @c msg will be returned.
        ///
        /// @param msg message to translate.
        /// @param registerNew whether or not the message must be created if translation not found.
        /// @return std::string_view translated message.
        /// @throw MessageNotFoundError when the translation is not found and @c registerNew is set to false.
        std::string_view translate(std::string_view msg, bool createNew = false) const;

      private:
        /// Current locale.
        std::string _locale;
        /// Loaded messages.
        std::map<std::string, std::string> _ressources;
    };

} // namespace localization

#endif /* !LOCALIZATION_RESSOURCEFILE_HPP_ */
