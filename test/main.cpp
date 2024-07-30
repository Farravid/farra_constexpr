#include <gtest/gtest.h>
#include "interval_map.hpp"

TEST(IntervalMapTest, Basic) 
{
    farra::flat_interval_map<int, char, 3> map { {{1, 'c'}}, 'z' };

    EXPECT_EQ(map[0], 'z');
    EXPECT_EQ(map[1], 'c');
}

TEST(IntervalMapTest, TestUpperBound) 
{
    farra::flat_interval_map<int, char, 3> map { {{1, 'c'}}, '.' };

    EXPECT_EQ(map.upper_bound(0)->second, 'c');
}

TEST(IntervalMapTest, keyBeginfirst) 
{
    farra::flat_interval_map<int, char, 5> map 
    { 
      {{1, 'B'}, {3, 'W'}, {4, '.'}, {6, 'D'}, {8, '.'}}, '.'
    };

    const farra::flat_interval_map<int, char, 5> map2
    { 
      {{1, 'B'}, {3, 'W'}, {4, '.'}, {6, 'D'}, {8, '.'}}, '.'
    };

    map.clear({'z'});
    map.assign(1,5, 'b');


    // EXPECT_EQ(map[0], '.');
    // EXPECT_EQ(map[1], 'B');
    // EXPECT_EQ(map[2], 'B');
    // EXPECT_EQ(map[3], 'W');
    // EXPECT_EQ(map[4], '.');
    // EXPECT_EQ(map[5], '.');
    // EXPECT_EQ(map[6], 'D');
    // EXPECT_EQ(map[7], 'D');
    // EXPECT_EQ(map[8], '.');
    // EXPECT_EQ(map[9], '.');
    // EXPECT_EQ(map[10], '.');

    // map.assign(0, 5, 'C');

    // EXPECT_EQ(map[0], 'C');
    // EXPECT_EQ(map[1], 'C');
    // EXPECT_EQ(map[2], 'C');
    // EXPECT_EQ(map[3], 'C');
    // EXPECT_EQ(map[4], 'C');
    // EXPECT_EQ(map[5], '.');
    // EXPECT_EQ(map[6], 'D');
    // EXPECT_EQ(map[7], 'D');
    // EXPECT_EQ(map[8], '.');
    // EXPECT_EQ(map[9], '.');
    // EXPECT_EQ(map[10], '.');
}
