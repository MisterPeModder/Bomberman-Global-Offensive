/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** test_ressource_file
*/

#include "Utils.hpp"
#include "localization/Localization.hpp"
#include "localization/RessourceFile.hpp"

#include <gtest/gtest.h>
#include <iostream>

using namespace localization;

static void init_locales() { Localization::setLocalesDirectory("localization/locales"); }

TEST(RessourceFile, uninitialized)
{
    RessourceFile file;

    ASSERT_TRUE(file.getLocale() == "");
    ASSERT_TRUE(isException<RessourceFile::LocaleNotSetError>([&]() { file.translate("Who are you ??"); }));
    ASSERT_TRUE(isException<RessourceFile::LocaleNotSetError>([&]() { file.save(); }));
    ASSERT_TRUE(isException<RessourceFile::LocaleNotSetError>([&]() { file.registerString("Who are you ??"); }));
    ASSERT_TRUE(isException<RessourceFile::LocaleNotSetError>([&]() { file.getFilePath(); }));
}

TEST(RessourceFile, unexisting_file)
{
    init_locales();

    RessourceFile file("unexisting");

    ASSERT_TRUE(!std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    file.save();
    ASSERT_TRUE(!std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
}

TEST(RessourceFile, new_file)
{
    init_locales();

    RessourceFile file("new");

    file.registerString("I am created!");
    ASSERT_TRUE(!std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    file.save();
    ASSERT_TRUE(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    std::filesystem::remove(Localization::getLocalePath("new"));
}

TEST(RessourceFile, translated_message)
{
    init_locales();

    RessourceFile file("hello");

    ASSERT_TRUE(file.translate("translated") == "traduit");
}

TEST(RessourceFile, untranslated_message)
{
    init_locales();

    RessourceFile file("hello");

    ASSERT_TRUE(file.translate("not translated") == "not translated");
}

TEST(RessourceFile, unregistered_message)
{
    init_locales();

    RessourceFile file("hello");

    ASSERT_TRUE(file.translate("????") == "????");
}

TEST(RessourceFile, switch_to_invalid_file)
{
    init_locales();

    RessourceFile file("hello");

    ASSERT_TRUE(file.translate("translated") == "traduit");
    file.loadLocale("unexisting");
    ASSERT_TRUE(!std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    ASSERT_TRUE(file.translate("translated") == "translated");
}

TEST(RessourceFile, loading_with_errors)
{
    init_locales();

    size_t count = 5;

    for (size_t i = 0; i < count; i++) {
        RessourceFile file("test_" + std::to_string(i));

        ASSERT_TRUE(file.translate("first message") == "premier message");
        ASSERT_TRUE(file.translate("multiple\nlines\nmessage") == "Message en\nplusieurs\nlignes");
        /// Invalid messages are ignored and so they are not translated.
        ASSERT_TRUE(file.translate("invalid") == "invalid");
    }
}
