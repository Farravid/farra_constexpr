#include "lifeobject.hpp"
#include "interval_map.hpp"
#include <map>

template <typename T>
constexpr void printContainer(T &container)
{
  for (const auto &item : container)
    std::println("{}, {}", item.first, item.second);
}

template <typename T>
constexpr void printArray(T &container)
{
  for (const auto &item : container)
    std::println("{}", item);
}

constexpr auto get_map_value()
{
  farra::flat_interval_map<int, char, 5> map{
      {{1, 'B'}, {3, 'W'}, {4, '.'}, {6, 'D'}, {8, '.'}}, '.'};

  map.clear({'z'});
  map.assign(1, 5, 'b');

  return map;
}

using LO = farra::LifeObject<1000>;
int main(int argc, char **argv)
{

  LO lo{};

  farra::flat_interval_map<int, LO, 1> im{};
  im.assign(1, 5, std::move(lo));

  return 0;
}