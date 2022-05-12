/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** RessourceFile
*/

#include "RessourceFile.hpp"
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
} // namespace localization