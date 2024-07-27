#include <print>
#include <string_view>
#include <map>

#include "interval_map.hpp"

template<typename T>
void printContainer(T& container)
{
  for(const auto& item : container)
    std::println("{}, {}", item.first, item.second);
}

int main()
{
  // constexpr farra::interval_map<uint8_t, float, 5> im = 
  // {
  //   {1, 1.1f},
  //   {5, 5.1f},
  //   {10, 10.1f},
  //   {15, 15.1f},
  //   {20, 20.1f},
  // };

  constexpr farra::map<int,int, 2> map = { {1,5}, {2,10} };
  //map.upper_bound(2);


  //std::array<std::pair<int, int>, 2> a { std::pair{1,1}, {2,2}};

  //auto is_greater = [](auto arrayKey) { return true; };
  //auto it = std::ranges::find_if(a, is_greater);

  //static_assert(map.cbegin()->second == 5);
  static_assert(map.upper_bound(1)->second == 10);

  //std::print("{}", map.upper_bound(4)->second);

  //std::array<std::pair<int, int>, 2> array { std::pair{1,5}, {2,10} };
}