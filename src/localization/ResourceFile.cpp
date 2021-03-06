/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** ResourceFile
*/

#include "ResourceFile.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include "Localization.hpp"
#include "logger/Logger.hpp"

namespace localization
{
    ResourceFile::LocaleNotFoundError::LocaleNotFoundError(std::string_view locale)
        : std::runtime_error(
            std::string("Locale file '") + Localization::getLocalePath(locale).generic_string() + "' not found.")
    {
    }

    ResourceFile::MessageNotFoundError::MessageNotFoundError(std::string_view locale, std::string_view message)
        : std::runtime_error(
            std::string("Message '") + message.data() + "' not found in locale '" + locale.data() + "'.")
    {
    }

    ResourceFile::LocaleNotSetError::LocaleNotSetError() : std::logic_error("No locale set.") {}

    ResourceFile::ResourceFile(std::string_view locale) { loadLocale(locale); }

    void ResourceFile::loadLocale(std::string_view locale)
    {
        _locale = locale;
        std::filesystem::path filepath = Localization::getLocalePath(_locale);
        std::ifstream file(filepath);
        std::string line;
        TokensVector tokens;

        _resources.clear();
        Logger::logger.log(Logger::Severity::Information, [&](std::ostream &writer) {
            writer << "Loading locale file '" << filepath << "' for locale '" << _locale << "'";
        });
        if (!file.is_open())
#ifdef BM_RELEASE
            throw LocaleNotFoundError(_locale);
#else
        {
            Logger::logger.log(Logger::Severity::Warning, [&](std::ostream &writer) {
                writer << "File not found, it will be created on save if messages are registered.";
            });
            return;
        }
#endif
        while (std::getline(file, line))
            tokens.push_back({getToken(line), line});
        tokens.push_back({getToken(line), line});
        parseTokens(tokens);
    }

    void ResourceFile::save()
    {
        if (_locale == "")
            throw LocaleNotSetError();
        if (_newResources.size() == 0)
            return;
        std::filesystem::path filepath = Localization::getLocalePath(_locale);
        std::ofstream file;

        Logger::logger.log(Logger::Severity::Information, [&](std::ostream &writer) {
            writer << "Updating locale file '" << filepath << "' for locale '" << _locale << "'";
        });
        file.open(filepath, std::ios_base::app | std::ios_base::out);
        if (!file.is_open())
            throw std::runtime_error("Unable to update locale file '" + filepath.generic_string() + "'.");
        for (auto iter = _newResources.begin(); iter != _newResources.end(); ++iter) {
            file << std::endl << "msgid ";
            writeMsg(file, iter->first);
            file << "msgstr ";
            writeMsg(file, iter->second);
        }
        _newResources.clear();
    }

    std::string_view ResourceFile::getLocale() const { return _locale; }

    std::filesystem::path ResourceFile::getFilePath() const
    {
        if (_locale == "")
            throw LocaleNotSetError();
        return Localization::getLocalePath(_locale);
    }

    std::string_view ResourceFile::translate(std::string_view msg)
    {
        std::string key(msg);

        if (_locale == "")
            throw LocaleNotSetError();
        if (_resources.find(key) == _resources.end())
#ifdef BM_RELEASE
            throw MessageNotFoundError(_locale, msg);
#else
            registerString(msg);
#endif
        if (_resources[key] == "")
            return msg;
        return _resources[key];
    }

    void ResourceFile::registerString(std::string_view msg, std::string_view translation)
    {
        std::string key(msg);

        if (_locale == "")
            throw LocaleNotSetError();
        if (_resources.find(key) != _resources.end() && (translation == "" || _resources[key] == translation))
            return;
        _resources[key] = translation;
        _newResources[key] = translation;
    }

    void ResourceFile::parseTokens(const TokensVector &tokens)
    {
        TokensVector::const_iterator iter = tokens.begin();

        consumeTokens({Token::EmptyLine, Token::Comment}, tokens, iter);
        while (iter != tokens.end()) {
            parseMessage(tokens, iter);
            if (iter != tokens.end())
                consumeTokens({Token::EmptyLine, Token::Comment}, tokens, ++iter);
        }
    }

    void ResourceFile::parseMessage(const TokensVector &tokens, TokensVector::const_iterator &iterator)
    {
        static auto logWarning = [&](std::string_view msg) {
            Logger::logger.log(Logger::Severity::Warning, [&](std::ostream &writer) {
                writer << "Invalid message (line " << iterator - tokens.begin() << "): " << msg;
            });
        };
        std::string id;
        std::string str;

        if (iterator->first == Token::MsgId || iterator->first == Token::MsgIdEmpty) {
            readMsg(iterator->first == Token::MsgIdEmpty, id, tokens, iterator);
            if (id.size() > 0) {
                if (iterator->first == Token::MsgStr || iterator->first == Token::MsgStrEmpty) {
                    readMsg(iterator->first == Token::MsgStrEmpty, str, tokens, iterator);
                    if (iterator->first == Token::EmptyLine)
                        _resources[id] = str;
                    else
                        logWarning("Messages must be separated by an empty line.");
                } else
                    logWarning("Messages must have a msgstr (even empty) after the msgid.");
            } else
                logWarning("Messages Id can't be empty, and multiline messages must end with a \\n.");
        } else
            logWarning("Start of message must be a msgid");
        consumeUntil(Token::EmptyLine, tokens, iterator);
        return;
    }

    void ResourceFile::skipComments(const TokensVector &tokens, TokensVector::const_iterator &iterator)
    {
        consumeTokens(Token::Comment, tokens, iterator);
    }

    void ResourceFile::consumeTokens(Token token, const TokensVector &tokens, TokensVector::const_iterator &iterator)
    {
        while (iterator != tokens.end() && iterator->first == token)
            ++iterator;
    }

    void ResourceFile::consumeTokens(
        const std::vector<Token> token, const TokensVector &tokens, TokensVector::const_iterator &iterator)
    {
        while (iterator != tokens.end() && std::find(token.begin(), token.end(), iterator->first) != token.end())
            ++iterator;
    }

    void ResourceFile::consumeUntil(Token token, const TokensVector &tokens, TokensVector::const_iterator &iterator)
    {
        while (iterator != tokens.end() && iterator->first != token)
            ++iterator;
    }

    void ResourceFile::readMsg(
        bool multiline, std::string &out, const TokensVector &tokens, TokensVector::const_iterator &iterator)
    {
        static std::regex singleLine("msg.+[ \t]+\"(.+)\"");
        static std::regex msgMultipleLines("\"(.+)(\\\\n)\"");
        std::smatch sm;

        if (multiline) {
            skipComments(tokens, ++iterator);
            while (iterator->first == Token::MsgMultiline) {
                std::regex_match(iterator->second, sm, msgMultipleLines);
                out += sm[1].str() + "\n";
                skipComments(tokens, ++iterator);
            }
            if (out.size() > 0 && out[out.size() - 1] == '\n')
                out.pop_back();
        } else {
            std::regex_match(iterator->second, sm, singleLine);
            out = sm[1].str();
            skipComments(tokens, ++iterator);
        }
    }

    void ResourceFile::writeMsg(std::ostream &stream, std::string_view msg)
    {
        if (msg.find('\n') == std::string::npos) {
            stream << "\"" << msg << "\"" << std::endl;
        } else {
            size_t start = 0;
            size_t end;

            stream << "\"\"" << std::endl;
            while ((end = msg.find('\n', start)) != std::string::npos) {
                std::cout << "'" << msg.substr(start, end) << "'" << std::endl;
                stream << "\"" << msg.substr(start, end - start) << "\\n\"" << std::endl;
                start = end + 1;
            }
            if (start < msg.size())
                stream << "\"" << msg.substr(start) << "\\n\"" << std::endl;
        }
    }

    ResourceFile::Token ResourceFile::getToken(const std::string &line)
    {
        static std::regex comment("[ \t]*#.*");
        static std::regex msgId("msgid[ \t]+\".+\"");
        static std::regex msgIdEmpty("msgid[ \t]+\"\"");
        static std::regex msgStr("msgstr[ \t]+\".+\"");
        static std::regex msgStrEmpty("msgstr[ \t]+\"\"");
        static std::regex msgMultipleLines("^[ \t]*\".+\\\\n\"");

        if (std::regex_match(line, comment))
            return Token::Comment;
        if (std::regex_match(line, msgId))
            return Token::MsgId;
        if (std::regex_match(line, msgIdEmpty))
            return Token::MsgIdEmpty;
        if (std::regex_match(line, msgStr))
            return Token::MsgStr;
        if (std::regex_match(line, msgStrEmpty))
            return Token::MsgStrEmpty;
        if (std::regex_match(line, msgMultipleLines))
            return Token::MsgMultiline;
        if (line == "")
            return Token::EmptyLine;
        return Token::Undefined;
    }

} // namespace localization
