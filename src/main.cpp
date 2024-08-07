#include "interval_map.hpp"
#include "function.hpp"
#include <print>
#include <vector>

// consteval auto get(int x)
// {
//     auto fn = [=](){ return x / 10; }; 
//     return fn;
// }

// consteval auto get_sum(int x)
// {
//     auto fn = [=](){ return x + 10; }; 
//     return fn;
// }

// consteval auto get_sub(int x)
// {
//     auto fn = [=](){ return x - 10; }; 
//     return fn;
// }

// consteval auto get_mult(int x)
// {
//     auto fn = [=](){ return x * 10; }; 
//     return fn;
// }

constexpr auto get_im()
{
    constexpr int value = 50; 
    constexpr auto fn = [=](){ return value / 10; }; 

    using map_t = farra::flat_interval_map<int, farra::function<int()>, 1>;
    using t = map_t::value_type;

    map_t im { t{1, fn} };
    return im;

    //std::vector<farra::function<int()>> v;
    //v.emplace_back(fn);

    //return v;
}



int main()
{
    static_assert(get_im()[0]() == 5);
}