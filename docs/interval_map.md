# farra::flat_interval_map
Yet another constexpr data structure for C++23  

`interval_map<K, V, std::size_t N>` is a data structure that efficiently associates intervals of keys of type K with values of type V. It is implemented on top of std::array, so we can say it is a flat interval map.

This data structure is useful when you want to store a certain value for a certain interval/range.
Some use cases are illustrated on [Use Cases](#use-cases)  

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
# Use Cases
## Avoiding branches for optimization
```C++
int main()
{
    //We can get rid of branches using interval maps
    //in a cleaner way and using less space than an array.

    int value = 40;

    //Instead of this
    // std::array<float, 160> values
    // {
    //     10.f, 10.f....
    //     20.f....
    //     40.f..... until 160 values;
    // }

    //Instead of this
    // if(value >= 1 && value <= 9) return 10.f;
    // if(value >= 10 && value <= 19) return 10.f;
    // if(value >= 20 && value <= 29) return 10.f;
    // ....


    //You have this
    using t = farra::flat_interval_map<int, float, 5>::value_type;
    constexpr farra::flat_interval_map<int, float, 5> map
    {
        -1,
        t{1, 10.f}, t{10, 20.f}, t{20, 40.f}, t{30, 80.f}, t{30, 160.f} 
    };


    return map[value];
}
```