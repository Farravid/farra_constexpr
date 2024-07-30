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

struct S{ std::array<int, 100>a{}; int value {}; };
int main(int argc, char **argv)
{
  //constexpr auto stuff = get_map_value();
  //printContainer(stuff);
  //static_assert(stuff[0] == 'z');

  farra::flat_interval_map<int, S, 2> im 
  { 
    {{1, S{ .value = 1} },
    {5, S{ .value = 5} }},
    S{ .value = 12}
  };

  std::map<int,float> map{};

  auto it = map.upper_bound(2);

  S& s = im[2];

  //auto upper = im.upper_bound(-20);

  //S& s = im[-20];

  //std::println("{}", s.value);

}