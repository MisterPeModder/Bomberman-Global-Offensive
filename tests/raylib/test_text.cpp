/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Raylib text module
*/

#include "raylib/text.hpp"

#include <gtest/gtest.h>
#include <string>

using namespace raylib::text;

TEST(pushUnicodeCodepoint, asciiChars)
{
    std::string buf;

    pushUnicodeCodepoint(buf, static_cast<int>('T'));
    pushUnicodeCodepoint(buf, static_cast<int>('e'));
    pushUnicodeCodepoint(buf, static_cast<int>('s'));
    pushUnicodeCodepoint(buf, static_cast<int>('t'));

    ASSERT_EQ(buf, "Test");
}

TEST(pushUnicodeCodepoint, latinChars)
{
    std::string buf;

    pushUnicodeCodepoint(buf, 0xE0);
    pushUnicodeCodepoint(buf, 0xE8);
    pushUnicodeCodepoint(buf, 0xAE);

    ASSERT_EQ(buf, "àè®");
}

TEST(pushUnicodeCodepoint, emoji)
{
    std::string buf;

    pushUnicodeCodepoint(buf, 0x1F346);
    pushUnicodeCodepoint(buf, 0x1F4A6);

    ASSERT_EQ(buf, "🍆💦");
}
