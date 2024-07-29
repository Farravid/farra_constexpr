#include <print>
#include <gtest/gtest.h>
#include "interval_map.hpp"
#include <map>

template<typename T>
constexpr void printContainer(T& container)
{
  for(const auto& item : container)
    std::println("{}, {}", item.first, item.second);
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

    printContainer(map);

    map.clear({'z'});
    map.assign(1,5, 'b');

    printContainer(map);

    //char& x = map[0];
    // char& x2 = map2[0];

    const std::map<int, int> mapstl {{1,2}};

    //int& x = mapstl[1];

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

template<typename T>
constexpr void printArray(T& container)
{
  for(const auto& item : container)
    std::println("{}", item);
}

constexpr auto get_map_value()
{
  farra::flat_interval_map<int, char, 5> map 
  { 
    {{1, 'B'}, {3, 'W'}, {4, '.'}, {6, 'D'}, {8, '.'}}, '.'
  };

  map.clear({'z'});
  map.assign(1,5, 'b');

  return map;
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  
  constexpr auto stuff = get_map_value();
  printContainer(stuff);
  static_assert(stuff[0] == 'z');

  //return RUN_ALL_TESTS();
}