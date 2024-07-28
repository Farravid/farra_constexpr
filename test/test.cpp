#include <gtest/gtest.h>
#include "../src/interval_map.hpp"

using namespace farra;

TEST(IntervalMapTest, Basic) 
{
    interval_map<int, char, 3> map { {1, 'c'} };

    EXPECT_EQ(map.upper_bound(0), 1);
}
