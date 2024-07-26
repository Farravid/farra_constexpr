#include <ranges>
#include <vector>
#include <string_view>
#include <print>
#include "interval_map.hpp"
#include "frozen/map.h"

int main()
{
  constexpr frozen::map<int, int, 1> map { {0,0} };

  auto even = [](int i) { return i & 1; };

  std::vector<int> v {1,2,3,4,5,6,7};
  constexpr farra::interval_map<std::string_view, int> im{};
  
  auto filtered = v | std::views::filter(even);

  std::print("{}", 5 * 4);
  return 0;
}