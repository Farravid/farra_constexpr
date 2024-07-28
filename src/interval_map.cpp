#include <print>
#//include <gtest/gtest.h>
#include "interval_map.hpp"

// TEST(IntervalMapTest, Basic) 
// {
//     farra::interval_map<int, char, 3> map { {1, 'c'} };

//     EXPECT_EQ(map.upper_bound(0)->second, 'c');
// }


template<typename T>
constexpr void printContainer(T& container)
{
  for(const auto& item : container)
    std::println("{}, {}", item.first, item.second);
}

template<typename T>
constexpr void printArray(T& container)
{
  for(const auto& item : container)
    std::println("{}", item);
}

constexpr auto get_map_value()
{
  farra::interval_map<int,char, 5> map{ {10, 'c'} };
  map.assign(3, 8, 'b');
  //map.assign(1, 2, 'a');
  //map.assign(20, 30, 'w');
  return map;
}

int main(int argc, char **argv)
{

  std::array<int, 5> a {1, 2, 3 ,4, 5};

  //farra::interval_map<int,char> map{ {1, 'a'}, {10, 'c'} };

  auto x = a | std::views::take(2);
  printArray(x);

  //testing::InitGoogleTest(&argc, argv);
  //return RUN_ALL_TESTS();
  
  constexpr auto stuff = get_map_value();
  //printContainer(stuff);
  //static_assert(stuff.upper_bound(2)->second == 'b');
  //static_assert(stuff.size() == 3);
}