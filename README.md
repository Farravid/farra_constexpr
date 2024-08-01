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

# Disclaimer
> This is just a learning project, nothing fancy production ready. In fact you can only use this for constexpr construction because there is no assign mehtod or something. That wasn't the goal of this project. 