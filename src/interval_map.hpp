#include <ranges>
#include <algorithm>
#include <limits>

//TODO: Include std::optional to allow for objects that are not default constructible
//TODO: Constexpr allocator tha fuck? 

template<typename T>
concept has_operator_less = requires(T&& type) { T{} < T{}; };

namespace farra
{
    template<typename _Key_t, typename _Value_t, std::size_t N = 5>
    requires has_operator_less<_Key_t>
    class interval_map
    {
    public:
        using key_type      = _Key_t;
        using mapped_type   = _Value_t;
        using value_type    = std::pair<_Key_t, _Value_t>;
        using storage_t     = std::array<std::pair<_Key_t, _Value_t>, N>;
        
        //TODO: Iterators could be typename storage_t::iterators...
        using const_pointer     = const value_type*;
        //TODO: Not sure about this
        using const_iterator    = const_pointer;
         
        constexpr interval_map(const std::initializer_list<value_type>& entries)
        {
            index_ = entries.size();
            std::ranges::copy(entries, container_.begin());
        }

        //TODO: Const correctness with C++23

        [[nodiscard]] constexpr const_iterator upper_bound(_Key_t key) const
        {
            //!!: Parameters are never gonna be constexpr, so assuming that a parameter is constexpr will make the compiler to fail. We should not assume that and just remove the constexpr, just mark the function as constexpr and if the compiler is able to do that the execution will be compilation time. constexpr auto is_greater is bad!! Explain in obsidian 

            //!!: Add the limits of std::vector constexpr, the memory should be freed before leaving the scope so there can't be any dynamic allocation becasuse we are in a constexpr world 

            auto is_greater = [key](auto arrayKey) { return arrayKey.first > key; };
            return std::ranges::find_if(container_, is_greater);
        }

        [[nodiscard]] constexpr const_iterator cbegin() const { return container_.cbegin(); }
        [[nodiscard]] constexpr const_iterator cend() const { return container_.cend(); }
        [[nodiscard]] constexpr const_iterator begin() const { return container_.begin(); }
        [[nodiscard]] constexpr const_iterator end() const { return container_.end(); }
        [[nodiscard]] constexpr std::size_t size() const { return container_.size(); }

        constexpr void assign(_Key_t keyBegin, _Key_t keyEnd, _Value_t value)
        {
            //TODO: Look for std::ranges::shift or similar
            if (keyBegin < cbegin()->first)
            {
                std::ranges::copy(container_ | std::views::take(index_), container_.begin() + 1);
                container_[0] = {keyBegin, value};
            }

            //std::ranges::copy()
            //container_[index_] = value_type {keyBegin, value};
            //++index_;
        }

    private:
        //It doesn't make a lot of sense to have an array what about look up or something like that in case the map wants to be used as a normal map?
        storage_t container_{};
        std::size_t index_{};
    };
}