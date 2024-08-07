#include "interval_map.hpp"
#include "function.hpp"
 #include <print>

struct S
{
    constexpr S(int x2) : x {x2}{}
    S() = delete;

    int x{};
	int y{};

    void func();
};

constexpr int get_5(int x, float y)
{
    return 5 + x + y;
}

constexpr auto test_empty()
{
    //farra::function f { [] { return 42; } };
    
    using t = decltype(&S::func);

    farra::function<int()> f { [] { return 42; } };
    return f;
}

int main()
{
    // using t = farra::flat_interval_map<int, float, 2>::value_type;
    // constexpr farra::flat_interval_map<int, float, 2> im
    // {
    //     5,
    //     t{1, 4.0f}, t{2, 5.0f} 
    // };

    // static_assert(!std::is_trivially_default_constructible_v<S>);
	// static_assert(im[-10].value() == 5.0f); 
	// static_assert(im[1].value() == 4); 
	// static_assert(im[2].value() == 5);
	// static_assert(im[7].value() == 5); l

    int x = 123;


    //static_assert(test_empty()() == 42);

    // constexpr farra::function<int()> f { []()
    // {
    //     return 12341;
    // } };

    //std::println("yes it is {}", f());
}