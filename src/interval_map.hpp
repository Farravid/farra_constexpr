#include <array>
#include <ranges>
#include <algorithm>
#include <concepts>

template<typename T>
concept has_operator_less = requires(T&& type) { T{} < T{}; };

namespace farra
{
    template<typename _Key_t, typename _Value_t, std::size_t N>
    requires has_operator_less<_Key_t>
    class map
    {
    public:
        using key_type      = _Key_t;
        using mapped_type   = _Value_t;
        using value_type    = std::pair<_Key_t, _Value_t>;
        
        using const_pointer     = const value_type*;
        //TODO: Not sure about this
        using const_iterator    = const_pointer;
         
        constexpr map(const std::initializer_list<value_type>& entries)
        {
            std::copy(entries.begin(), entries.end(), container_.begin());
        }

        //TODO: Const correctness with C++23

        [[nodiscard]] constexpr const_iterator upper_bound(_Key_t key) const
        {
            //!!: Parameters are never gonna be constexpr, so assuming that a parameter is constexpr will make the compiler to fail. We should not assume that and just remove the constexpr, just mark the function as constexpr and if the compiler is able to do that the execution will be compilation time. constexpr auto is_greater is bad!! Explain in obsidian 

            auto is_greater = [key](auto arrayKey) { return arrayKey.first > key; };
            return std::ranges::find_if(container_, is_greater);
        }

        constexpr const_iterator cbegin() const { return container_.cbegin(); }
        constexpr const_iterator cend() const { return container_.cend(); }

    private:
        //It doesn't make a lot of sense to have an array what about look up or something like that in case the map wants to be used as a normal map?
        using Container_t = std::array<std::pair<_Key_t, _Value_t>, N>;
        Container_t container_{};
    };
}