/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** test_ressource_file
*/

#include <iostream>
#include <criterion/criterion.h>
#include "Utils.hpp"
#include "localization/Localization.hpp"
#include "localization/RessourceFile.hpp"

using namespace localization;

static void init_locales() { Localization::setLocalesDirectory("tests/localization/locales"); }

Test(RessourceFile, uninitialized)
{
    RessourceFile file;

    cr_assert(file.getLocale() == "");
    cr_assert(isException<RessourceFile::LocaleNotSetError>([&]() { file.translate("Who are you ??"); }));
    cr_assert(isException<RessourceFile::LocaleNotSetError>([&]() { file.save(); }));
    cr_assert(isException<RessourceFile::LocaleNotSetError>([&]() { file.registerString("Who are you ??"); }));
    cr_assert(isException<RessourceFile::LocaleNotSetError>([&]() { file.getFilePath(); }));
}

Test(RessourceFile, unexisting_file, .init = init_locales)
{
    RessourceFile file("unexisting");

    cr_assert(!std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    file.save();
    cr_assert(!std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
}

Test(RessourceFile, new_file, .init = init_locales)
{
    RessourceFile file("new");

    file.registerString("I am created!");
    cr_assert(!std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    file.save();
    cr_assert(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    std::filesystem::remove(Localization::getLocalePath("new"));
}

Test(RessourceFile, translated_message, .init = init_locales)
{
    RessourceFile file("hello");

    cr_assert(file.translate("translated") == "traduit");
}

Test(RessourceFile, untranslated_message, .init = init_locales)
{
    RessourceFile file("hello");

    cr_assert(file.translate("not translated") == "not translated");
}

Test(RessourceFile, unregistered_message, .init = init_locales)
{
    RessourceFile file("hello");

    cr_assert(file.translate("????") == "????");
}

Test(RessourceFile, switch_to_invalid_file, .init = init_locales)
{
    RessourceFile file("hello");

    cr_assert(file.translate("translated") == "traduit");
    file.loadLocale("unexisting");
    cr_assert(!std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    cr_assert(file.translate("translated") == "translated");
}

Test(RessourceFile, loading_with_errors, .init = init_locales)
{
    size_t count = 5;

    for (size_t i = 0; i < count; i++) {
        RessourceFile file("test_" + std::to_string(i));

        cr_assert(file.translate("first message") == "premier message");
        cr_assert(file.translate("multiple\nlines\nmessage") == "Message en\nplusieurs\nlignes");
        /// Invalid messages are ignored and so they are not translated.
        cr_assert(file.translate("invalid") == "invalid");
    }
}