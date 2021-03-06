/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** ResourceFile
*/

#ifndef LOCALIZATION_RESOURCEFILE_HPP_
#define LOCALIZATION_RESOURCEFILE_HPP_

#include <filesystem>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <string_view>

namespace localization
{
    /// File regrouping multiple @ref ResourceString in the same locale.
    class ResourceFile {
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

        /// Exception thrown when the locale isn't set (unititialized) on translate/register operations.
        class LocaleNotSetError : public std::logic_error {
          public:
            /// @brief Construct a new Locale Not Set Error object
            LocaleNotSetError();
        };

        /// Construct a new Resource File object. The object is invalid until a successfull call to @ref
        /// loadLocale() is made.
        ResourceFile() = default;

        /// Construct a new Resource File object with a given locale.
        /// @note The file will be searched in the path given by @ref Localization::getLocalesDirectory().
        ///
        /// @param locale locale to load.
        /// @throw LocaleNotFoundError when the locale can't be found in release mode, in debug mode create the file.
        ResourceFile(std::string_view locale);

        /// Destroy the Resource File object.
        ~ResourceFile() = default;

        /// Load a locale file.
        /// @note If the file can't be found in debug mode, it is created on save when new messages are registered.
        ///
        /// @param locale country code ("en", "fr"...)
        /// @throw LocaleNotFoundError when the locale can't be found in release mode.
        void loadLocale(std::string_view locale);

        /// Save the locale file.
        ///
        /// @throw LocaleNotSetError when the locale isn't set.
        void save();

        /// Get the loaded locale.
        /// @warning If no locale is set, an empty string is returned.
        ///
        /// @return std::string_view loaded locale.
        std::string_view getLocale() const;

        /// Get the path of the locale file.
        /// @note The file might not exist if save() wasn't called yet.
        ///
        /// @return std::filesystem::path path of the locale file.
        /// @throw LocaleNotSetError when the locale isn't set.
        std::filesystem::path getFilePath() const;

        /// Translate a message in the loaded locale.
        /// @note If the translation is found but is empty, @c msg will be returned.
        /// @note If no locale is set, @c msg will be returned.
        ///
        /// @param msg message to translate.
        /// @return std::string_view translated message.
        /// @throw MessageNotFoundError when the translation is not found in release mode, in debug mode create the
        /// message.
        /// @throw LocaleNotSetError when the locale isn't set.
        std::string_view translate(std::string_view msg);

        /// Register a new string in the loaded locale.
        /// @note If the string is already set and has the same translation, does nothing.
        /// @note The string will be added at the end of the file on save.
        ///
        /// @param msg message id.
        /// @param translation message translation.
        ///
        /// @throw LocaleNotSetError when the locale isn't set.
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

        /// Parse a message (msgid - msgstr) and register it to the known resources.
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

        /// Skip all the @c token tokens.
        ///
        /// @param token list of token to consume.
        /// @param tokens list of tokens corresponding to the locale file.
        /// @param iterator current iterator.
        static void consumeTokens(
            const std::vector<Token> token, const TokensVector &tokens, TokensVector::const_iterator &iterator);

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

        /// Write the content of a msgid/msgstr in @c stream.
        /// @note This function is used to handle multiline messages.
        ///
        /// @param stream output stream (locale file).
        /// @param msg content to write.
        static void writeMsg(std::ostream &stream, std::string_view msg);

        /// Current locale.
        std::string _locale;
        /// Loaded messages.
        std::map<std::string, std::string> _resources;
        /// New messages (to save).
        std::map<std::string, std::string> _newResources;
    };

} // namespace localization

#endif /* !LOCALIZATION_RESOURCEFILE_HPP_ */
