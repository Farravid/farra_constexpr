#include "interval_map.hpp"
#include "function.hpp"
#include <print>
#include <vector>

constexpr auto get_fn()
{
    farra::function f { []{ return 5 / 10; } }; 
    return f;
}

constexpr auto get_v()
{
    std::vector<farra::function<int()>> v {};
    v.push_back(get_fn());
    return v;
}

constexpr auto get_im()
{
    using map_t = farra::flat_interval_map<int, farra::function<int()>, 1>;
    using t = map_t::value_type;

    map_t im { t{1, get_fn()} };
    
    return im;
}

int main()
{
    static_assert(get_fn()() == 0);
    static_assert(get_v()[0]() == 0);
    static_assert(get_im()[0]() == 0); //It doesn't compile
}