/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** BitSet unit tests
*/

#include <gtest/gtest.h>

#include "util/BitSet.hpp"

TEST(BitSet, init)
{
    util::BitSet empty;
    util::BitSet word(64);
    util::BitSet beeg(420);
    util::BitSet fromStr("1000101");

    EXPECT_EQ(empty.size(), 0);
    EXPECT_EQ(word.size(), 64);

    for (std::size_t i = 0; i < 64; ++i)
        EXPECT_FALSE(word[i]) << "index was " << i;
    for (std::size_t i = 0; i < 420; ++i)
        EXPECT_FALSE(beeg[i]) << "index was " << i;
    EXPECT_TRUE(fromStr[0]);
    EXPECT_FALSE(fromStr[1]);
    EXPECT_TRUE(fromStr[2]);
    EXPECT_FALSE(fromStr[3]);
    EXPECT_FALSE(fromStr[4]);
    EXPECT_FALSE(fromStr[5]);
    EXPECT_TRUE(fromStr[6]);
}

TEST(BitSet, set)
{
    util::BitSet set("0111001000");

    set.set(0);
    EXPECT_TRUE(set.test(0));
    set.set(0, false);
    EXPECT_FALSE(set.test(0));

    set.setAll();
    EXPECT_EQ(set, util::BitSet("1111111111"));
    set.setAll(false);
    EXPECT_EQ(set, util::BitSet("0000000000"));
}

TEST(BitSet, Reference)
{
    util::BitSet set(21);

    EXPECT_FALSE(set[2]);
    set[2] = true;
    EXPECT_TRUE(set[2]);
    set[2] = false;
    EXPECT_FALSE(set[2]);

    set[1].flip();
    EXPECT_TRUE(set[1]);
    set[1].flip();
    EXPECT_FALSE(set[1]);

    util::BitSet::Reference ref = set[3];
    EXPECT_FALSE(ref);
    EXPECT_TRUE(~ref);
}

TEST(BitSet, flippinBits)
{
    util::BitSet set("110100100");
    util::BitSet flipped = ~set;

    EXPECT_EQ(set, util::BitSet("110100100"));
    EXPECT_EQ(flipped, util::BitSet("001011011"));
    set.flip();
    EXPECT_EQ(set, util::BitSet("001011011"));
}

TEST(BitSet, operations)
{
    EXPECT_EQ(util::BitSet("111") & util::BitSet("11011100"), util::BitSet("100"));
    EXPECT_EQ(util::BitSet("111") | util::BitSet("11011100"), util::BitSet("111"));
    EXPECT_EQ(util::BitSet("111") ^ util::BitSet("11011100"), util::BitSet("011"));

    util::BitSet set1("11011100");
    util::BitSet set2("11011100");
    util::BitSet set3("11011100");

    set1 &= util::BitSet("111");
    set2 |= util::BitSet("111");
    set3 ^= util::BitSet("111");

    EXPECT_EQ(set1, util::BitSet("100"));
    EXPECT_EQ(set2, util::BitSet("111"));
    EXPECT_EQ(set3, util::BitSet("011"));
}

TEST(BitSet, pushPop)
{
    util::BitSet set;

    set.push(1);
    set.push(0);
    set.push(1);
    set.push(1);
    set.push(0);

    EXPECT_EQ(set, util::BitSet("01101"));

    EXPECT_FALSE(set.pop());
    EXPECT_TRUE(set.pop());
    EXPECT_TRUE(set.pop());

    EXPECT_EQ(set, util::BitSet("01"));
}