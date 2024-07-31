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

using LO = farra::LifeObject;
int main(int argc, char **argv)
{

  // using type = std::pair<int,LO>;
  // farra::flat_interval_map<int, LO, 2> im
  // {
  //   true, type{10, LO{}}, type{20, LO{}} 
  // };

  

  auto it = im.find(20);

  //printContainer(im);

  //im.assign(1, 5, LO{});

  return 0;
}