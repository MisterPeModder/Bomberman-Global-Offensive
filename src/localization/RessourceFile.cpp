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

    RessourceFile::~RessourceFile() { save(); }

    void RessourceFile::loadLocale(std::string_view locale, bool createNew)
    {
        std::string filepath = Localization::getLocalePath(locale);
        std::ifstream file(filepath);
        std::string line;
        // Token expected = Token::MsgId;
        // Token token;

        if (!file.is_open()) {
            if (createNew) {
                std::ofstream newFile(filepath);

                newFile.close();
                return;
            } else
                throw LocaleNotFoundError(locale);
        }
        while (std::getline(file, line)) {
            std::cout << "Token " << static_cast<int>(getToken(line)) << ": " << line << std::endl;
        }
        /// Parse
    }

    void RessourceFile::save() {}

    std::string_view RessourceFile::getLocale() const { return _locale; }

    std::string_view RessourceFile::translate(std::string_view msg, bool createNew)
    {
        std::string_view res;
        std::string key(msg);

        try {
            res = _ressources.at(key);
        } catch (std::out_of_range &) {
            if (!createNew)
                throw MessageNotFoundError(_locale, msg);
            _ressources[key] = "";
            res = "";
        }
        if (res == "")
            return msg;
        return res;
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