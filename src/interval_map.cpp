#include <ranges>
#include <vector>
#include <string_view>
#include <print>
#include "interval_map.hpp"

int main()
{
  auto even = [](int i) { return i & 1; };

  std::vector<int> v {1,2,3,4,5,6,7};
  constexpr farra::interval_map<std::string_view, int> im{};
  
  //auto filtered = v | std::views::filter(even);

  return 0;
}