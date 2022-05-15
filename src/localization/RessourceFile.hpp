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
#include <vector>
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
        /// @param createNew whether or not the file must be created if not found.
        /// @throw LocaleNotFoundError when the locale can't be found and @c createNew is set to false.
        RessourceFile(std::string_view locale, bool createNew = false);

        /// Destroy the Ressource File object.
        ~RessourceFile() = default;

        /// Load a locale file.
        ///
        /// @param locale country code ("en", "fr"...)
        /// @param createNew whether or not the file must be created if not found.
        /// @throw LocaleNotFoundError when the locale can't be found and @c createNew is set to false.
        void loadLocale(std::string_view locale, bool createNew = false);

        /// Save the locale file.
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
        std::string_view translate(std::string_view msg, bool createNew = false);

        /// Register a new string in the loaded locale.
        /// @note If the string is already set and has the same translation, does nothing.
        /// @note The string will be added at the end of the file on save.
        ///
        /// @param msg message id.
        /// @param translation message translation.
        void registerString(std::string_view msg, std::string_view translation = "");

      private:
        enum class Token {
            Undefined,
            Comment,
            MsgId,
            MsgIdEmpty,
            MsgStr,
            MsgStrEmpty,
            MsgMultiline,
            EmptyLine,
        };

        using TokensVector = std::vector<std::pair<Token, std::string>>;

        /// Get the Token corresponding to the line sent.
        ///
        /// @param line line to analyse.
        /// @return Token corresponding token.
        static Token getToken(const std::string &line);

        /// Parse the list of tokens corresponding to a locale file.
        /// @note Invalid messages will be ignored and won't throw exceptions, they will instead write a warning in the
        /// global logger.
        ///
        /// @param tokens list of tokens corresponding to the locale file.
        void parseTokens(const TokensVector &tokens);

        /// Parse a message (msgid - msgstr) and register it to the known ressources.
        /// @note Messages must be separated by empty lines.
        ///
        /// @param tokens list of tokens corresponding to the locale file.
        /// @param iterator current iterator.
        void parseMessage(const TokensVector &tokens, TokensVector::const_iterator &iterator);

        /// Skip all the Comment tokens.
        ///
        /// @param tokens list of tokens corresponding to the locale file.
        /// @param iterator current iterator.
        static void skipComments(const TokensVector &tokens, TokensVector::const_iterator &iterator);

        /// Skip all the @c token tokens.
        ///
        /// @param token token to consume.
        /// @param tokens list of tokens corresponding to the locale file.
        /// @param iterator current iterator.
        static void consumeTokens(Token token, const TokensVector &tokens, TokensVector::const_iterator &iterator);

        /// Consume all the tokens until a @c token is found.
        ///
        /// @param token token to found.
        /// @param tokens list of tokens corresponding to the locale file.
        /// @param iterator current iterator.
        static void consumeUntil(Token token, const TokensVector &tokens, TokensVector::const_iterator &iterator);

        /// Read the content of a msgid/msgstr in @c out.
        ///
        /// @param multiline whether or not the message is multiline or not (multiline messages start with msgid/str
        /// "").
        /// @param out string containing the content of the message.
        /// @param tokens list of tokens corresponding to the locale file.
        /// @param iterator current iterator.
        static void readMsg(
            bool multiline, std::string &out, const TokensVector &tokens, TokensVector::const_iterator &iterator);

        /// Current locale.
        std::string _locale;
        /// Loaded messages.
        std::map<std::string, std::string> _ressources;
        /// New messages (to save).
        std::map<std::string, std::string> _newRessources;
    };

} // namespace localization

#endif /* !LOCALIZATION_RESSOURCEFILE_HPP_ */
