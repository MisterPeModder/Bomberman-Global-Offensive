/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** RessourceFile
*/

#include "RessourceFile.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include "Localization.hpp"
#include "logger/Logger.hpp"

namespace localization
{
    RessourceFile::LocaleNotFoundError::LocaleNotFoundError(std::string_view locale)
        : std::runtime_error(std::string("Locale file '") + Localization::getLocalePath(locale) + "' not found.")
    {
    }

    RessourceFile::MessageNotFoundError::MessageNotFoundError(std::string_view locale, std::string_view message)
        : std::runtime_error(
            std::string("Message '") + message.data() + "' not found in locale '" + locale.data() + "'.")
    {
    }

    RessourceFile::RessourceFile(std::string_view locale, bool createNew) { loadLocale(locale, createNew); }

    void RessourceFile::loadLocale(std::string_view locale, bool createNew)
    {
        _locale = locale;
        std::string filepath = Localization::getLocalePath(_locale);
        std::ifstream file(filepath);
        std::string line;
        TokensVector tokens;

        Logger::logger.log(Logger::Severity::Information, [&](std::ostream &writer) {
            writer << "Loading locale file '" << filepath << "' for locale '" << _locale << "'";
        });
        if (!file.is_open()) {
            if (createNew) {
                std::ofstream newFile(filepath);

                newFile.close();
                return;
            } else
                throw LocaleNotFoundError(_locale);
        }
        while (std::getline(file, line))
            tokens.push_back({getToken(line), line});
        tokens.push_back({getToken(line), line});
        parseTokens(tokens);
    }

    void RessourceFile::save()
    {
        if (_newRessources.size() == 0)
            return;
        std::string filepath = Localization::getLocalePath(_locale);
        std::ofstream file;

        Logger::logger.log(Logger::Severity::Information, [&](std::ostream &writer) {
            writer << "Updating locale file '" << filepath << "' for locale '" << _locale << "'";
        });
        file.open(filepath, std::ios_base::app | std::ios_base::out);
        if (!file.is_open())
            throw std::runtime_error("Unable to update locale file '" + filepath + "'.");
        for (auto iter = _newRessources.begin(); iter != _newRessources.end(); ++iter) {
            file << std::endl << "msgid \"" << iter->first << "\"" << std::endl;
            file << "msgstr \"" << iter->second << "\"" << std::endl;
        }
        _newRessources.clear();
    }

    std::string_view RessourceFile::getLocale() const { return _locale; }

    std::string_view RessourceFile::translate(std::string_view msg, bool createNew)
    {
        std::string key(msg);

        if (_ressources.find(key) == _ressources.end()) {
            if (!createNew)
                throw MessageNotFoundError(_locale, msg);
            registerString(msg);
        }
        if (_ressources[key] == "")
            return msg;
        return _ressources[key];
    }

    void RessourceFile::registerString(std::string_view msg, std::string_view translation)
    {
        std::string_view res;
        std::string key(msg);

        if (_ressources.find(key) != _ressources.end() && (translation == "" || _ressources[key] == translation))
            return;
        _ressources[key] = translation;
        _newRessources[key] = translation;
    }

    void RessourceFile::parseTokens(const TokensVector &tokens)
    {
        TokensVector::const_iterator iter = tokens.begin();

        while (iter != tokens.end()) {
            parseMessage(tokens, iter);
            consumeTokens(Token::EmptyLine, tokens, ++iter);
        }
    }

    void RessourceFile::parseMessage(const TokensVector &tokens, TokensVector::const_iterator &iterator)
    {
        static auto logWarning = [&](std::string_view msg) {
            Logger::logger.log(Logger::Severity::Warning, [&](std::ostream &writer) {
                writer << "Invalid message (line " << iterator - tokens.begin() << "): " << msg;
            });
        };
        std::string id;
        std::string str;

        skipComments(tokens, iterator);
        if (iterator->first == Token::MsgId || iterator->first == Token::MsgIdEmpty) {
            readMsg(iterator->first == Token::MsgIdEmpty, id, tokens, iterator);
            if (id.size() > 0) {
                if (iterator->first == Token::MsgStr || iterator->first == Token::MsgStrEmpty) {
                    readMsg(iterator->first == Token::MsgStrEmpty, str, tokens, iterator);
                    if (iterator->first == Token::EmptyLine)
                        _ressources[id] = str;
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

    void RessourceFile::skipComments(const TokensVector &tokens, TokensVector::const_iterator &iterator)
    {
        consumeTokens(Token::Comment, tokens, iterator);
    }

    void RessourceFile::consumeTokens(Token token, const TokensVector &tokens, TokensVector::const_iterator &iterator)
    {
        while (iterator != tokens.end() && iterator->first == token)
            ++iterator;
    }

    void RessourceFile::consumeUntil(Token token, const TokensVector &tokens, TokensVector::const_iterator &iterator)
    {
        while (iterator != tokens.end() && iterator->first != token)
            ++iterator;
    }

    void RessourceFile::readMsg(
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

    RessourceFile::Token RessourceFile::getToken(const std::string &line)
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
