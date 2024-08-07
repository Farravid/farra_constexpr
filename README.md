# farra_interval_map
Yet another constexpr data structure for C++23  

`interval_map<K, V, std::size_t N>` is a data structure that efficiently associates intervals of keys of type K with values of type V. It is implemented on top of std::array, so we can say it is a flat interval map.

This data structure is useful when you want to store a certain value for a certain interval/range.
Some use cases are illustrated on [Use Cases](#UseCases)  

> This is just a learning project, nothing fancy production ready. In fact you can only use this for constexpr construction because there is no assign mehtod or something. That wasn't the goal of this project :). 

# Setup
> For a header only setup you can switch to the include branch

After cloning the repo, you only need to build the project with the handy bash script.

This is the synstax for `build.sh` 
```bash
./build.sh [target, default=interval_map] [build_type, default=Release]
```
So these are all the targets available
```bash
./build.sh test #will execute the tests
./build.sh benchmark #will execute the benchmarks
./build.sh all #will execute all
```
Remember you can add Debug after the target name in order to build the debug libraries 

## Dependencies
* C++23
* GCC 14.1
* Conan
* CMake

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

# What did I refresh/learn?
* C++
  * `constexpr`
  * Data structures
  * `<ranges>`
  * `<concepts>`
  * C++23 deducing `this`
  * Perfect forwarding (`std::forward`)
  * Lifetime of objects (thanks to `lifeobject.hpp`)
  * CTAD
* Tools and libraries
  * Google benchmark library
  * Google test library (gtest)
  * Conan package manager
  * CMake 