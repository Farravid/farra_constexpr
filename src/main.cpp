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