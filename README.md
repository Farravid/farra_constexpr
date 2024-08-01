# farra_interval_map
Yet another constexpr data structure for C++23  

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

# What did I refresh/learn?
* C++
  * `constexpr`
  * Data structures
  * `<ranges>`
  * `<concepts>`
  * C++23 deducing `this`
  * Perfect forwarding (`std::forward`)
  * Lifetime of objects (thanks to `lifeobject.hpp`)
* Tools and libraries
  * Google benchmark library
  * Google test library (gtest)
  * Conan package manager
  * CMake 