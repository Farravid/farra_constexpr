# farra_interval_map
Yet another constexpr data structure for C++23

# Setup
Just include the ```include``` folder on your compile path.
## Dependencies
* C++23
* GCC 14.1

# Usage

```C++
#include "interval_map.hpp"

int main()
{
	using im_t = farra::flat_interval_map<int, char, 5>;
	using t = im_t::value_type;

	constexpr im_t im 
	{
		'Z', //default value
		t{1, 'A'}, t{5, 'C'}, t{10, 'V'}, t{12, 'W'}, t{15, 'Z'} 
	};

	static_assert(im[-10] == 'Z');
	static_assert(im[2] == 'A');
	static_assert(im[7] == 'C');
	static_assert(im[11] == 'V');
	static_assert(im[12] == 'W');
	static_assert(im[17] == 'Z');
}
```
> In case the of not default constructible

```C++
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
```

# Disclaimer
> This is just a learning project, nothing fancy production ready. In fact you can only use this for constexpr construction because there is no assign mehtod or something. That wasn't the goal of this project. 