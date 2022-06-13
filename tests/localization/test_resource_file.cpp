/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** test_resource_file
*/

#include "localization/Localization.hpp"
#include "localization/ResourceFile.hpp"

#include <gtest/gtest.h>
#include <iostream>

using namespace localization;

static void init_locales() { Localization::setLocalesDirectory("localization/locales"); }

TEST(ResourceFile, uninitialized)
{
    ResourceFile file;

    EXPECT_EQ(file.getLocale(), "");
    EXPECT_THROW(file.translate("Who are you ??"), ResourceFile::LocaleNotSetError);
    EXPECT_THROW(file.save(), ResourceFile::LocaleNotSetError);
    EXPECT_THROW(file.registerString("Who are you ??"), ResourceFile::LocaleNotSetError);
    EXPECT_THROW(file.getFilePath(), ResourceFile::LocaleNotSetError);
}

TEST(ResourceFile, unexisting_file)
{
    init_locales();

    ResourceFile file;

#ifdef BM_RELEASE
    EXPECT_THROW(file.loadLocale("unexisting"), ResourceFile::LocaleNotFoundError);
#else
    file.loadLocale("unexisting");
#endif

    ASSERT_FALSE(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    file.save();
    ASSERT_FALSE(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
}

TEST(ResourceFile, new_file)
{
    init_locales();

    ResourceFile file;

#ifdef BM_RELEASE
    EXPECT_THROW(file.loadLocale("new"), ResourceFile::LocaleNotFoundError);
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

TEST(ResourceFile, translated_message)
{
    init_locales();

    ResourceFile file("hello");

    ASSERT_EQ(file.translate("translated"), "traduit");
}

TEST(ResourceFile, untranslated_message)
{
    init_locales();

    ResourceFile file("hello");

    ASSERT_EQ(file.translate("not translated"), "not translated");
}

TEST(ResourceFile, unregistered_message)
{
    init_locales();

    ResourceFile file("hello");

#ifdef BM_RELEASE
    EXPECT_THROW(file.translate("????"), ResourceFile::MessageNotFoundError);
#else
    ASSERT_EQ(file.translate("????"), "????");
#endif
}

TEST(ResourceFile, switch_to_invalid_file)
{
    init_locales();

    ResourceFile file("hello");

    ASSERT_EQ(file.translate("translated"), "traduit");
#ifdef BM_RELEASE
    EXPECT_THROW(file.loadLocale("unexisting"), ResourceFile::LocaleNotFoundError);
    ASSERT_FALSE(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    EXPECT_THROW(file.translate("translated"), ResourceFile::MessageNotFoundError);
#else
    file.loadLocale("unexisting");
    ASSERT_FALSE(std::filesystem::exists(Localization::getLocalePath(file.getLocale())));
    ASSERT_EQ(file.translate("translated"), "translated");
#endif
}

TEST(ResourceFile, loading_with_errors)
{
    init_locales();

    size_t count = 5;

    for (size_t i = 0; i < count; i++) {
        ResourceFile file("test_" + std::to_string(i));

        ASSERT_EQ(file.translate("first message"), "premier message");
        ASSERT_EQ(file.translate("multiple\nlines\nmessage"), "Message en\nplusieurs\nlignes");
// Invalid messages are ignored and so they are not translated.
#ifdef BM_RELEASE
        EXPECT_THROW(file.translate("invalid"), ResourceFile::MessageNotFoundError);
#else
        ASSERT_EQ(file.translate("invalid"), "invalid");
#endif
    }
}
