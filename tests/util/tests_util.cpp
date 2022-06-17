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

TEST(insertUtf8Codepoint, asciiChars)
{
    std::string buf;

    insertUtf8Codepoint(buf, static_cast<int>('T'));
    insertUtf8Codepoint(buf, static_cast<int>('e'));
    insertUtf8Codepoint(buf, static_cast<int>('s'));
    insertUtf8Codepoint(buf, static_cast<int>('t'));

    ASSERT_EQ(buf, "Test");
}

TEST(insertUtf8Codepoint, latinChars)
{
    std::string buf;

    insertUtf8Codepoint(buf, 0xE0);
    insertUtf8Codepoint(buf, 0xE8);
    insertUtf8Codepoint(buf, 0xAE);

    ASSERT_EQ(buf, "àè®");
}

TEST(insertUtf8Codepoint, emoji)
{
    std::string buf;

    insertUtf8Codepoint(buf, 0x1F346);
    insertUtf8Codepoint(buf, 0x1F4A6);

    ASSERT_EQ(buf, "🍆💦");
}

TEST(removeUtf8Codepoint, asciiChars)
{
    std::string buf = "Test";

    EXPECT_EQ(removeUtf8Codepoint(buf), {static_cast<int>('t'), 1});
    EXPECT_EQ(buf.size(), 3);

    EXPECT_EQ(removeUtf8Codepoint(buf), {static_cast<int>('s'), 1});
    EXPECT_EQ(buf.size(), 2);

    EXPECT_EQ(removeUtf8Codepoint(buf), {static_cast<int>('e'), 1});
    EXPECT_EQ(buf.size(), 1);

    EXPECT_EQ(removeUtf8Codepoint(buf), {static_cast<int>('T'), 1});
    EXPECT_EQ(buf.size(), 0);
}

TEST(removeUtf8Codepoint, hybrid)
{
    std::string buf = "ᚦéjà?🤔";

    EXPECT_EQ(removeUtf8Codepoint(buf), {0x1F914, 4});
    EXPECT_EQ(buf.size(), 9);

    EXPECT_EQ(removeUtf8Codepoint(buf), {static_cast<int>('?'), 1});
    EXPECT_EQ(buf.size(), 8);

    EXPECT_EQ(removeUtf8Codepoint(buf), {0xE0, 2});
    EXPECT_EQ(buf.size(), 6);

    EXPECT_EQ(removeUtf8Codepoint(buf), {static_cast<int>('j'), 1});
    EXPECT_EQ(buf.size(), 5);

    EXPECT_EQ(removeUtf8Codepoint(buf), {0xE9, 2});
    EXPECT_EQ(buf.size(), 3);

    EXPECT_EQ(removeUtf8Codepoint(buf), {0x16A6, 3});
    EXPECT_EQ(buf.size(), 0);

    EXPECT_EQ(removeUtf8Codepoint(buf), {0, 0});
    EXPECT_EQ(buf.size(), 0);
}

TEST(removeUtf8Codepoint, midString)
{
    std::string buf = "ᚦéjà?🤔";

    EXPECT_EQ(removeUtf8Codepoint(buf, 1), {0x16A6, 3});
    EXPECT_EQ(buf, "éjà?🤔")

    EXPECT_EQ(removeUtf8Codepoint(buf, 7), {0x1F914, 4});
    EXPECT_EQ(buf, "éjà?")
}
