/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Utilities test
*/

#include "util/util.hpp"

#include <gtest/gtest.h>
#include <string>

using namespace util;

TEST(pushUtf8Codepoint, asciiChars)
{
    std::string buf;

    pushUtf8Codepoint(buf, static_cast<int>('T'));
    pushUtf8Codepoint(buf, static_cast<int>('e'));
    pushUtf8Codepoint(buf, static_cast<int>('s'));
    pushUtf8Codepoint(buf, static_cast<int>('t'));

    ASSERT_EQ(buf, "Test");
}

TEST(pushUtf8Codepoint, latinChars)
{
    std::string buf;

    pushUtf8Codepoint(buf, 0xE0);
    pushUtf8Codepoint(buf, 0xE8);
    pushUtf8Codepoint(buf, 0xAE);

    ASSERT_EQ(buf, "àè®");
}

TEST(pushUtf8Codepoint, emoji)
{
    std::string buf;

    pushUtf8Codepoint(buf, 0x1F346);
    pushUtf8Codepoint(buf, 0x1F4A6);

    ASSERT_EQ(buf, "🍆💦");
}

TEST(popUtf8Codepoint, asciiChars)
{
    std::string buf = "Test";

    EXPECT_EQ(popUtf8Codepoint(buf), static_cast<int>('t'));
    EXPECT_EQ(buf.size(), 3);

    EXPECT_EQ(popUtf8Codepoint(buf), static_cast<int>('s'));
    EXPECT_EQ(buf.size(), 2);

    EXPECT_EQ(popUtf8Codepoint(buf), static_cast<int>('e'));
    EXPECT_EQ(buf.size(), 1);

    EXPECT_EQ(popUtf8Codepoint(buf), static_cast<int>('T'));
    EXPECT_EQ(buf.size(), 0);
}

TEST(popUtf8Codepoint, hybrid)
{
    std::string buf = "ᚦéjà?🤔";

    EXPECT_EQ(popUtf8Codepoint(buf), 0x1F914);
    EXPECT_EQ(buf.size(), 9);

    EXPECT_EQ(popUtf8Codepoint(buf), static_cast<int>('?'));
    EXPECT_EQ(buf.size(), 8);

    EXPECT_EQ(popUtf8Codepoint(buf), 0xE0);
    EXPECT_EQ(buf.size(), 6);

    EXPECT_EQ(popUtf8Codepoint(buf), static_cast<int>('j'));
    EXPECT_EQ(buf.size(), 5);

    EXPECT_EQ(popUtf8Codepoint(buf), 0xE9);
    EXPECT_EQ(buf.size(), 3);

    EXPECT_EQ(popUtf8Codepoint(buf), 0x16A6);
    EXPECT_EQ(buf.size(), 0);

    EXPECT_EQ(popUtf8Codepoint(buf), 0);
    EXPECT_EQ(buf.size(), 0);
}
