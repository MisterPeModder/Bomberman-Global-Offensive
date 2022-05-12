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
} // namespace localization