/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** test_loadConfigFile
*/

#include <gtest/gtest.h>

#include "util/util.hpp"

TEST(loadConfigFile, unexisting_file)
{
    EXPECT_FALSE(util::loadConfigFile("unexisting", [](std::string_view key, std::string_view value) {
        (void)key;
        (void)value;
        return true;
    }));
}

TEST(loadConfigFile, empty)
{
    /// An empty file shouldn't call the lambda since it has no key value pair
    EXPECT_TRUE(util::loadConfigFile("configs/empty.cfg", [](std::string_view key, std::string_view value) {
        (void)key;
        (void)value;
        return false;
    }));
}

TEST(loadConfigFile, no_key_value)
{
    /// A file with only empty lines/comments shouldn't call the lambda since it has no key value pair
    EXPECT_TRUE(util::loadConfigFile("configs/no_key.cfg", [](std::string_view key, std::string_view value) {
        (void)key;
        (void)value;
        return false;
    }));
}

TEST(loadConfigFile, multiple_formats)
{
    std::vector<std::pair<std::string, std::string>> expected = {
        {"simple", "value"},
        {"with spaces ", " a spaced value"},
        {"using:namespace:like", "value"},
        {"stop", "at=first=equal"},
        {"no_value", ""},
        {"", "no_key"},
        {"last", "valid"},
    };

    size_t id = 0;
    EXPECT_TRUE(util::loadConfigFile("configs/test.cfg", [&](std::string_view key, std::string_view value) {
        EXPECT_EQ(key, expected[id].first);
        EXPECT_EQ(value, expected[id].second);
        ++id;
        return true;
    }));
}

TEST(loadConfigFile, stop_no_key)
{
    std::vector<std::pair<std::string, std::string>> expected = {
        {"simple", "value"},
        {"with spaces ", " a spaced value"},
        {"using:namespace:like", "value"},
        {"stop", "at=first=equal"},
        {"no_value", ""},
        {"", "no_key"},
        {"last", "valid"},
    };

    size_t id = 0;
    /// When returning false in the lambda it stops the parsing and return false
    EXPECT_FALSE(util::loadConfigFile("configs/test.cfg", [&](std::string_view key, std::string_view value) {
        EXPECT_EQ(key, expected[id].first);
        EXPECT_EQ(value, expected[id].second);
        ++id;
        return !key.empty();
    }));
}