#include <print>
#include "interval_map.hpp"
#include <map>

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
  constexpr auto stuff = get_map_value();
  printContainer(stuff);
  static_assert(stuff[0] == 'z');

  //return RUN_ALL_TESTS();
}