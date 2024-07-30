#include <ranges>
#include <algorithm>
#include "util.hpp"

//TODO: Include std::optional to allow for objects that are not default constructible
//TODO: Constexpr allocator tha fuck? 
//TODO: Understand iterators stuff

namespace farra
{
    template<typename _Key_t, typename _Value_t, std::size_t N = 5>
    requires has_operator_less<_Key_t>
    class flat_interval_map
    {
    public:
        //=========================================================================
		// Type aliases
		//=========================================================================
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

        using a_key_type                = avoid_copy_t<key_type>;
        using ca_key_type               = avoid_copy_t<const key_type>;
        using a_mapped_type             = avoid_copy_t<mapped_type>;
        using ca_mapped_type            = avoid_copy_t<const mapped_type>;

        //=========================================================================
		// Constructors
		//=========================================================================
        explicit constexpr flat_interval_map(const std::initializer_list<value_type>& entries)
            : index_ {entries.size()}
        {
            std::ranges::copy(entries, container_.begin());
        }

        explicit constexpr flat_interval_map(const std::initializer_list<value_type>& entries, const mapped_type& value)
            : index_ {entries.size()}
            , initialValue_ {value}
        {
            std::ranges::copy(entries, container_.begin());
        }

        explicit constexpr flat_interval_map(avoid_copy_t<const mapped_type> value)
            : initialValue_ {value}
        {
            std::ranges::fill(container_, value_type{0, value});
        }

        //=========================================================================
		// Element access
		//=========================================================================
        // [[nodiscard]] constexpr auto&& operator[](this auto&& self, const key_type&& key)
        // {
        //     //TODO: Check this since is not returning the references as it should be
        //     auto upper = self.upper_bound(key);
        //     return upper == self.container_.cbegin() 
        //         ? std::forward<decltype(self)>(self).initialValue_
        //         : std::prev(upper)->second;
        // }

        [[nodiscard]] constexpr const mapped_type& operator[](const key_type&& key) const
        {
            auto upper = upper_bound(key);
            return upper == fbegin() 
                ? initialValue_
                : std::prev(upper)->second;
        }

        [[nodiscard]] constexpr mapped_type& operator[](const key_type&& key)
        {
            auto upper = upper_bound(key);
            return upper == fbegin() 
                ? initialValue_
                : std::prev(upper)->second;
        }

        //=========================================================================
		// Iterators
		//=========================================================================
        [[nodiscard]] constexpr auto fbegin(this auto&& self) noexcept { return &self.container_; }
        [[nodiscard]] constexpr auto fend(this auto&& self) noexcept { return &self.container_ + self.index_; }
        //[[nodiscard]] constexpr const_iterator fend(this auto&& self) noexcept { return container_.cbegin(); }
        [[nodiscard]] constexpr const_iterator cbegin() const noexcept { return container_.cbegin(); }
        [[nodiscard]] constexpr const_iterator cend() const noexcept { return cbegin() + index_; }
        [[nodiscard]] constexpr const_iterator begin() const noexcept { return container_.begin(); }
        [[nodiscard]] constexpr const_iterator end() const noexcept { return begin() + index_; }

        //=========================================================================
		// Capacity
		//=========================================================================
        [[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }
        [[nodiscard]] constexpr std::size_t size() const noexcept { return index_; }
        [[nodiscard]] constexpr std::size_t max_size() const noexcept { return container_.max_size(); }

        //=========================================================================
		// Modifiers
		//=========================================================================
        constexpr void assign(ca_key_type keyBegin, ca_key_type keyEnd, ca_mapped_type value)
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

        constexpr void clear(std::optional<mapped_type> value = {})
        {
            index_ = 0;
            if(value.has_value()) 
                initialValue_ = value.value();
        }

        //=========================================================================
		// Lookup
		//=========================================================================
        //TODO: C++23 const correctness too!!!
        [[nodiscard]] constexpr const_iterator upper_bound(_Key_t key) const
        {
            auto is_greater = [key](auto arrayKey) { return arrayKey.first > key; };
            return std::ranges::find_if(container_, is_greater);
        }

        [[nodiscard]] constexpr const_iterator lower_bound(_Key_t key) const
        {
			auto is_not_less = [key](auto arrayKey) { return arrayKey.first >= key; };
			return std::ranges::find_if(container_, is_not_less);
        }

        [[nodiscard]] constexpr bool contains(ca_key_type key) const
        {
            return std::ranges::contains(container_, key);
        } 


    private:
        storage_type container_{};
        std::size_t index_{};
        mapped_type initialValue_{};
    };
}