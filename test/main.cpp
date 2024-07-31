#include <gtest/gtest.h>
#include "interval_map.hpp"
#include "lifeobject.hpp"

template <typename T>
constexpr void printContainer(T &container)
{
  for (const auto &item : container)
    std::println("{}, {}", item.first, item.second);
}

TEST(IntervalMapTest, SingleAssign) 
{
	farra::flat_interval_map<int, char, 2> im {'A'};
	im.assign(1,4,'B');

	EXPECT_EQ(im[0], 'A');
	EXPECT_EQ(im[1], 'B');
	EXPECT_EQ(im[2], 'B');
	EXPECT_EQ(im[3], 'B');
	EXPECT_EQ(im[4], 'A');
	EXPECT_EQ(im[5], 'A');
	EXPECT_EQ(im.size(), 2);
}

TEST(IntervalMapTest, FirstKeyBiggerOrSame) 
{
	farra::flat_interval_map<int, char, 2> im {'A'};
	im.assign(4,4,'B');
	im.assign(8,4,'B');

	EXPECT_EQ(im[0], 'A');
	EXPECT_EQ(im[1], 'A');
	EXPECT_EQ(im[2], 'A');
	EXPECT_EQ(im[3], 'A');
	EXPECT_EQ(im[4], 'A');
	EXPECT_EQ(im[5], 'A');
	EXPECT_EQ(im.size(), 0);
}

TEST(IntervalMapTest, ThreeAssign)
{
	farra::flat_interval_map<int, char, 4> im {'A'};
    im.assign(1, 4, 'B');
    im.assign(3, 6, 'C');
    im.assign(4, 8, 'B');

	printContainer(im);

	EXPECT_EQ(im[0], 'A');
	EXPECT_EQ(im[1], 'B');
	EXPECT_EQ(im[2], 'B');
	EXPECT_EQ(im[3], 'C');
	EXPECT_EQ(im[4], 'B');
	EXPECT_EQ(im[5], 'B');
	EXPECT_EQ(im[6], 'B');
	EXPECT_EQ(im[7], 'B');
	EXPECT_EQ(im[8], 'A');
	EXPECT_EQ(im.size(), 2);
}

TEST(IntervalMapTest, FirstEntrySameValue) 
{
	farra::flat_interval_map<int, char> im {'A'};
    im.assign(1, 5, 'A');
	EXPECT_EQ(im.size(), 0);
}