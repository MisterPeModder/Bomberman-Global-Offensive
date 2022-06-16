/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Raylib text module
*/

#include "raylib/text/text.hpp"

#include <gtest/gtest.h>
#include <utility>
#include <string_view>

using namespace raylib::text;
using namespace std::string_view_literals;

TEST(codepointToUtf8, base)
{
    EXPECT_EQ(codepointToUtf8(0x2A), "*"sv);
    EXPECT_EQ(codepointToUtf8(0xE9), "é"sv);
    EXPECT_EQ(codepointToUtf8(0x16A6), "ᚦ"sv);
    EXPECT_EQ(codepointToUtf8(0x1F914), "🤔"sv);
}

TEST(utf8ToCodepoint, base)
{
    EXPECT_EQ(utf8ToCodepoint("*"sv), std::make_pair(0x2A, std::size_t(1)));
    EXPECT_EQ(utf8ToCodepoint("é"sv), std::make_pair(0xE9, std::size_t(2)));
    EXPECT_EQ(utf8ToCodepoint("ᚦ"sv), std::make_pair(0x16A6, std::size_t(3)));
    EXPECT_EQ(utf8ToCodepoint("🤔"sv), std::make_pair(0x1F914, std::size_t(4)));
}
