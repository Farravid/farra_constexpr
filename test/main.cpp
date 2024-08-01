#include <gtest/gtest.h>
#include "interval_map.hpp"
#include "lifeobject.hpp"

template <typename T>
constexpr void printContainer(T &container)
{
  for (const auto &item : container)
    std::println("{}, {}", item.first, item.second);
}

void cleanLifeObject()
{
	farra::LifeObject::timesConstructor = 0;
	farra::LifeObject::timesCopyConstructor = 0;
	farra::LifeObject::timesMoveConstructor = 0;
	farra::LifeObject::timesCopyAssignment = 0;
	farra::LifeObject::timesMoveAssignment = 0;
	farra::LifeObject::timesDestructor = 0;
}

TEST(IntervalMapTest, ZeroCopyConstructor) 
{
	cleanLifeObject();
	using LO = farra::LifeObject;
	using map_pair = std::pair<int,LO>;
	farra::flat_interval_map<int, LO, 5> map 
	{ 
		LO{}, map_pair{1, LO{}}, map_pair{3, LO{}}, map_pair{4, LO{}}, map_pair{6, LO{}}, map_pair{8, LO{}}
	};

	EXPECT_EQ(LO::timesCopyConstructor, 0);
	EXPECT_EQ(LO::timesCopyAssignment, 0);
}

TEST(IntervalMapTest, ZeroCopyConstructorValue) 
{
	cleanLifeObject();
	using LO = farra::LifeObject;
	using map_pair = std::pair<int,LO>;
	farra::flat_interval_map<int, LO, 0> map{ LO{} };

	LO lo{};
	farra::flat_interval_map<int, LO, 0> map2{ std::move(lo) };

	EXPECT_EQ(LO::timesCopyConstructor, 0);
	EXPECT_EQ(LO::timesCopyAssignment, 0);
}

TEST(IntervalMapTest, EmptyMapAccess) 
{
	constexpr farra::flat_interval_map<int, char, 0> map3{ 'Z' };
	EXPECT_EQ(map3[123], 'Z');
	EXPECT_EQ(map3[0], 'Z');
}

TEST(IntervalMapTest, SomeAccess) 
{
	using map = farra::flat_interval_map<uint8_t,char, 12>;
	using t = map::value_type;
	constexpr map map3
	{ 
		'Z',
		t{1, 'C'}, t{4, 'D'}, t{5, 'Z'}, t{7, 'J'},
		t{9, 'C'}, t{10, 'D'}, t{12, 'Z'}, t{14, 'H'},
		t{15, 'C'}, t{21, 'D'}, t{43, 'Z'}, t{50, 'Z'}
	};

	EXPECT_EQ(map3[123], 'Z');
	EXPECT_EQ(map3[0], 'Z');
	EXPECT_EQ(map3[5], 'Z');
	EXPECT_EQ(map3[42], 'D');
	EXPECT_EQ(map3[12], 'Z');
	EXPECT_EQ(map3[32], 'D');
	EXPECT_EQ(map3[8], 'J');
	EXPECT_EQ(map3[20], 'C');
}

TEST(IntervalMapTest, Contains) 
{
	using map = farra::flat_interval_map<uint8_t,char>;
	using type = map::value_type;
	constexpr map im { 'B', type{1, 'A'}, type{5, 'C'}, type{10, 'B'}};

	EXPECT_TRUE(im.contains(5));
	EXPECT_FALSE(im.contains(12));

	constexpr map im2 {'C'};
	EXPECT_FALSE(im2.contains(2));
}

TEST(IntervalMapTest, Clear) 
{
	farra::flat_interval_map<int, char> im {'A'};
	EXPECT_EQ(im[2], 'A');
	im.clear();
	EXPECT_EQ(im[2], 'A');
	EXPECT_EQ(im.size(), 0);
}

TEST(IntervalMapTest, ClearAndNewBaseValue) 
{
	farra::flat_interval_map<int, char> im {'A'};
	EXPECT_EQ(im[2], 'A');
	im.clear('B');
	EXPECT_EQ(im[2], 'B');
	EXPECT_EQ(im.size(), 0);
}