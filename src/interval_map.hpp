#include <ranges>
#include <algorithm>

//TODO: Include std::optional to allow for objects that are not default constructible
//TODO: Constexpr allocator tha fuck? 
//TODO: Understand iterators stuff

template<typename T>
concept has_operator_less = requires(T&& type) { T{} < T{}; };

namespace farra
{
    template<typename _Key_t, typename _Value_t, std::size_t N = 5>
    requires has_operator_less<_Key_t>
    class flat_interval_map
    {
    public:
        using key_type          		= _Key_t;
        using mapped_type       		= _Value_t;
        using value_type        		= std::pair<_Key_t, _Value_t>;
        //key_compare
        using storage_type        		= std::array<value_type, N>;
        using reference         		= std::pair<const key_type&, mapped_type&>;
        using const_reference   		= std::pair<const key_type&, const mapped_type&>;
        using size_type         		= std::size_t;
        //difference_type
        using iterator          		= typename storage_type::iterator;
        using const_iterator    		= typename storage_type::const_iterator;
        using reverse_iterator  		= typename storage_type::iterator;
        using const_reverse_iterator 	= typename storage_type::const_iterator;

        constexpr flat_interval_map(const std::initializer_list<value_type>& entries)
        {
            index_ = entries.size();
            std::ranges::copy(entries, container_.begin());
        }

        constexpr flat_interval_map(const mapped_type& value)
            : initialValue_ {value}
        {
            std::ranges::fill(container_, value_type{0, value});
        }

        //TODO: Const correctness with C++23

        [[nodiscard]] constexpr const_iterator upper_bound(_Key_t key) const
        {
            //!!: Parameters are never gonna be constexpr, so assuming that a parameter is constexpr will make the compiler to fail. We should not assume that and just remove the constexpr, just mark the function as constexpr and if the compiler is able to do that the execution will be compilation time. constexpr auto is_greater is bad!! Explain in obsidian 

            //!!: Add the limits of std::vector constexpr, the memory should be freed before leaving the scope so there can't be any dynamic allocation becasuse we are in a constexpr world 

            auto is_greater = [key](auto arrayKey) { return arrayKey.first > key; };
            return std::ranges::find_if(container_, is_greater);
        }

        // [[nodiscard]] constexpr const_iterator lower_bound(_Key_t key) const
        // {
		// 	auto is_not_less = [key](auto arrayKey) { return arrayKey.first >= key; };
		// 	return std::ranges::find_if(container_, is_not_less);
        // }

		template<typename Self>
		[[nodiscard]] constexpr auto lower_bound(this Self&& self, _Key_t key)
		{
			auto is_not_less = [key](auto arrayKey) { return arrayKey.first >= key; };
			return std::ranges::find_if(self->container_, is_not_less);
		}

        //TODO: We can avoid repeating with deducing this but that would not be friendly with stl containers I guess 
        [[nodiscard]] constexpr const_iterator cbegin() const noexcept { return container_.cbegin(); }
        [[nodiscard]] constexpr const_iterator cend() const noexcept { return cbegin() + index_; }
        [[nodiscard]] constexpr const_iterator begin() const noexcept { return container_.begin(); }
        [[nodiscard]] constexpr const_iterator end() const noexcept { return begin() + index_; }

        [[nodiscard]] constexpr std::size_t size() const noexcept { return index_; }
        [[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }


        constexpr void assign(_Key_t keyBegin, _Key_t keyEnd, _Value_t value)
        {
            //TOOD: Check arihtmetics
            if(empty() && value != initialValue_) 
            {
                container_[0] = value_type{keyBegin, value};
                container_[1] = value_type{keyEnd, initialValue_};
                index_ = 2;
                return;
            }

            if (keyBegin < cbegin()->first)
            {
                std::shift_right(container_.begin(), container_.end(), 1);
                container_[0] = {keyBegin, value};
                ++index_;
            }

            //std::ranges::copy()
            //container_[index_] = value_type {keyBegin, value};
            //++index_;
        }

    private:
        storage_type container_{};
        std::size_t index_{};
        mapped_type initialValue_{};
    };
}