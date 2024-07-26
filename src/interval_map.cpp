#include <ranges>
#include <vector>
#include <print>

int main()
{
  auto even = [](int i) { return i & 1; };

  std::vector<int> v {1,2,3,4,5,6,7};
  
  auto filtered = v | std::views::filter(even);

  for(int x : filtered)
    std::println("{}", x);
}