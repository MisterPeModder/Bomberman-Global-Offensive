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

    std::filesystem::path Localization::getLocalePath(std::string_view locale)
    {
        return std::filesystem::path(getLocalesDirectory()).append(std::string("locale_") + locale.data() + ".po");
    }

    void Localization::setLocale(std::string_view locale)
    {
        std::string key(locale);

        if (_Instance._locales.find(key) == _Instance._locales.end())
            _Instance._locales.insert({key, ResourceFile(locale)});
        _Instance._locale = key;
    }

    void Localization::saveLocales()
    {
        std::filesystem::create_directories(Localization::getLocalesDirectory());
        for (auto it : _Instance._locales)
            it.second.save();
    }

    std::string_view Localization::getLocale() { return _Instance._locale; }

    void Localization::loadLocales(const std::vector<std::string_view> &locales)
    {
        for (const std::string_view &loc : locales)
            _Instance._locales[std::string(loc)] = ResourceFile(loc);
    }

    std::string_view Localization::translate(std::string_view msg)
    {
#ifndef BM_RELEASE
        registerString(msg);
#endif
        if (_Instance._locale == "")
            return msg;
        return _Instance._locales[_Instance._locale].translate(msg);
    }

    void Localization::registerString(std::string_view msg)
    {
        for (auto iter = _Instance._locales.begin(); iter != _Instance._locales.end(); ++iter)
            iter->second.registerString(msg);
    }

    Localization::Localization() : _localesDirectory("locales") {}
} // namespace localization
