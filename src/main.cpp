#include "interval_map.hpp"
#include "function.hpp"

constexpr auto get_add()   { return farra::function{ [](int x, int y){ return x + y; } }; }
constexpr auto get_sub()   { return farra::function{ [](int x, int y){ return x - y; } }; }
constexpr auto get_mul()   { return farra::function{ [](int x, int y){ return x * y; } }; }
constexpr auto get_div()   { return farra::function{ [](int x, int y){ return x / y; } }; }

constexpr auto get_im()
{
	using im_t = farra::flat_interval_map<int, farra::function<int(int, int)>, 4>;
	using t = im_t::value_type;

	im_t im
	{
		get_add(),
		t{1, get_add()}, t{10, get_sub()}, t{20, get_mul()}, t{30, get_div()}
	};

	return im;
}

int main()
{
	static_assert(get_im()[0](10,10) == 20);
	static_assert(get_im()[12](10,10) == 0);
	static_assert(get_im()[25](10,10) == 100);
	static_assert(get_im()[35](10,10) == 1);
}