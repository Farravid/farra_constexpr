#include "interval_map.hpp"

struct S
{
    constexpr S(int x2) : x {x2}{}
    S() = delete;

    int x{};
	int y{};
};

int main()
{
    using t = farra::flat_interval_map<int, S, 2>::value_type;
    constexpr farra::flat_interval_map<int, S, 2> im
    {
        5,
        t{1, 4}, t{2, 5} 
    };

    static_assert(!std::is_trivially_default_constructible_v<S>);
	static_assert(im[-10].x == 5); 
	static_assert(im[1].x == 4); 
	static_assert(im[2].x == 5);
	static_assert(im[7].x == 5); 
}