/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Localization
*/

#include "Localization.hpp"

namespace localization
{
    Localization Localization::_Instance;

    void Localization::setLocalesDirectory(const std::filesystem::path &directory)
    {
        _Instance._localesDirectory = directory;
    }

    const std::filesystem::path &Localization::getLocalesDirectory() { return _Instance._localesDirectory; }

    std::string Localization::getLocalePath(std::string_view locale)
    {
        return std::filesystem::path(getLocalesDirectory())
            .append(std::string("locale_") + locale.data() + ".po")
            .generic_string();
    }

    void Localization::setLocale(std::string_view locale, bool createNew)
    {
        std::string key(locale);

        if (_Instance._locales.find(key) == _Instance._locales.end())
            _Instance._locales.insert({key, RessourceFile(locale, createNew)});
        _Instance._locale = key;
    }

    void Localization::saveLocales()
    {
        for (auto it : _Instance._locales)
            it.second.save();
    }

    std::string_view Localization::getLocale() { return _Instance._locale; }

    void Localization::loadLocales(const std::vector<std::string_view> &locales, bool createNew)
    {
        for (const std::string_view &loc : locales)
            _Instance._locales[std::string(loc)] = RessourceFile(loc, createNew);
    }

    std::string_view Localization::translate(std::string_view msg, bool registerNew)
    {
        if (registerNew)
            registerString(msg);
        if (_Instance._locale == "")
            return msg;
        return _Instance._locales[_Instance._locale].translate(msg, registerNew);
    }

    void Localization::registerString(std::string_view msg)
    {
        for (auto iter = _Instance._locales.begin(); iter != _Instance._locales.end(); ++iter)
            iter->second.registerString(msg);
    }

    Localization::Localization() : _localesDirectory("locales") {}
} // namespace localization
