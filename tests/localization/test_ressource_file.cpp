/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** test_ressource_file
*/

#include "localization/Localization.hpp"
#include "localization/RessourceFile.hpp"

#include <gtest/gtest.h>
#include <iostream>

using namespace localization;

static void init_locales() { Localization::setLocalesDirectory("localization/locales"); }

TEST(RessourceFile, uninitialized)
{
    RessourceFile file;

    EXPECT_EQ(file.getLocale(), "");
    EXPECT_THROW(file.translate("Who are you ??"), RessourceFile::LocaleNotSetError);
    EXPECT_THROW(file.save(), RessourceFile::LocaleNotSetError);
    EXPECT_THROW(file.registerString("Who are you ??"), RessourceFile::LocaleNotSetError);
    EXPECT_THROW(file.getFilePath(), RessourceFile::LocaleNotSetError);
}

TEST(RessourceFile, unexisting_file)
{
    init_locales();

    RessourceFile file;

#ifdef BM_RELEASE
    EXPECT_THROW(file.loadLocale("unexisting"), RessourceFile::LocaleNotFoundError);
#else
    file.loadLocale("unexisting");
#endif

    ASSERT_FALSE(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    file.save();
    ASSERT_FALSE(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
}

TEST(RessourceFile, new_file)
{
    init_locales();

    RessourceFile file;

#ifdef BM_RELEASE
    EXPECT_THROW(file.loadLocale("new"), RessourceFile::LocaleNotFoundError);
    ASSERT_FALSE(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
#else
    file.loadLocale("new");
    file.registerString("I am created!");
    ASSERT_FALSE(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    file.save();
    ASSERT_TRUE(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    std::filesystem::remove(Localization::getLocalePath("new"));
#endif
}

TEST(RessourceFile, translated_message)
{
    init_locales();

    RessourceFile file("hello");

    ASSERT_EQ(file.translate("translated"), "traduit");
}

TEST(RessourceFile, untranslated_message)
{
    init_locales();

    RessourceFile file("hello");

    ASSERT_EQ(file.translate("not translated"), "not translated");
}

TEST(RessourceFile, unregistered_message)
{
    init_locales();

    RessourceFile file("hello");

#ifdef BM_RELEASE
    EXPECT_THROW(file.translate("????"), RessourceFile::MessageNotFoundError);
#else
    ASSERT_EQ(file.translate("????"), "????");
#endif
}

TEST(RessourceFile, switch_to_invalid_file)
{
    init_locales();

    RessourceFile file("hello");

    ASSERT_EQ(file.translate("translated"), "traduit");
#ifdef BM_RELEASE
    EXPECT_THROW(file.loadLocale("unexisting"), RessourceFile::LocaleNotFoundError);
    ASSERT_FALSE(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    EXPECT_THROW(file.translate("translated"), RessourceFile::MessageNotFoundError);
#else
    file.loadLocale("unexisting");
    ASSERT_FALSE(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    ASSERT_EQ(file.translate("translated"), "translated");
#endif
}

TEST(RessourceFile, loading_with_errors)
{
    init_locales();

    size_t count = 5;

    for (size_t i = 0; i < count; i++) {
        RessourceFile file("test_" + std::to_string(i));

        ASSERT_EQ(file.translate("first message"), "premier message");
        ASSERT_EQ(file.translate("multiple\nlines\nmessage"), "Message en\nplusieurs\nlignes");
// Invalid messages are ignored and so they are not translated.
#ifdef BM_RELEASE
        EXPECT_THROW(file.translate("invalid"), RessourceFile::MessageNotFoundError);
#else
        ASSERT_EQ(file.translate("invalid"), "invalid");
#endif
    }
}
