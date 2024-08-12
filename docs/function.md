# farra::function

Constexpr version of `std::function` using new C++23 `constexpr std::unique_ptr`.
The functioning is pretty similar to `std::function` but it doesn't cover all the functionalities of the stl version.

**CTAD** guides added for better usage.

`farra::function` adds straight-forward **support for member functions** without any additional calls.

# Usage

```C++
#include "function.hpp"

constexpr float fn(float x, float y) { return x / y; }

struct S
{
	constexpr float fn(float add) const //Make sure to add const to your member function in order to work!!
	{
		return 40.f / 10.f + add;
	}
};

constexpr auto get_free_fn()    { return farra::function{ fn }; }
constexpr auto get_lambda()     { return farra::function{ []{ return 20 / 10; } }; }
constexpr auto get_lambda_2()   { return farra::function{ [x = 10]{ return 20 / 10 + x; } }; }
constexpr auto get_lambda_3()   { return farra::function{ [x = 10] (int y) { return 20 / 10 + x + y; } }; }
constexpr auto get_member_fn()	{ return farra::function{ &S::fn }; }


int main()
{
	static_assert(get_free_fn()(10.f,20.f) == 0.5f);
	static_assert(get_lambda()() == 2);
	static_assert(get_lambda_2()() == 12);
	static_assert(get_lambda_3()(20) == 32);

	constexpr S s{};
	static_assert(get_member_fn()(s, 20.f) == 24.f);
}
```
# flat_interval_map
We can also use `farra::function` in combination with `farra::flat_interval_map`   
Quite cool honestly, so definitely check it out [here!](interval_map.md#use-cases)

# Use Cases
The use cases are pretty much the same as `std::function`, just be creative and use it wherever you find it useful!   
Feel free to share it here! So I can add it to this document.


