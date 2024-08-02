#include <ranges>
#include "util.hpp"
namespace farra
{
    template<typename _Key_t, typename _Value_t, std::size_t N = 5>
    class flat_interval_map
    {
    public:
        //=========================================================================
		// Type aliases
		//=========================================================================
        using key_type          		= _Key_t;
        using mapped_type       		= _Value_t;
        using value_type        		= std::pair<if_optional_t<_Key_t>, if_optional_t<_Value_t>>;
        using storage_type        		= std::array<value_type, N>;
        using reference         		= std::pair<const key_type&, mapped_type&>;
        using const_reference   		= std::pair<const key_type&, const mapped_type&>;
        using size_type         		= std::size_t;
        using iterator          		= typename storage_type::iterator;
        using const_iterator    		= typename storage_type::const_iterator;
        using reverse_iterator  		= typename storage_type::iterator;
        using const_reverse_iterator 	= typename storage_type::const_iterator;

        using a_key_type                = avoid_copy_t<key_type>;
        using a_mapped_type             = avoid_copy_t<mapped_type>;

        //=========================================================================
		// Constructors
		//=========================================================================
        template<typename... Args>
        requires less_than<N, Args...>
        explicit constexpr flat_interval_map(a_mapped_type&& value, Args&&... entries)
            : index_{sizeof...(Args)}
            , container_{std::forward<Args>(entries)...} 
            , initialValue_ {std::forward<a_mapped_type>(value)}
        {};

        explicit constexpr flat_interval_map(a_mapped_type&& value) noexcept
            : initialValue_ {std::forward<a_mapped_type>(value)}
        {}

        //=========================================================================
		// Element access
		//=========================================================================
        [[nodiscard]] constexpr auto&& operator[](this auto&& self, a_key_type key)
        {
            if(self.empty()) return self.initialValue_;

            auto upper = self.upper_bound(key);
            return upper == self.fbegin()
                  ? self.initialValue_
                  : std::prev(upper)->second;
        }

        //=========================================================================
		// Iterators
		//=========================================================================
        [[nodiscard]] constexpr auto fbegin(this auto&& self) noexcept { return &self.container_[0]; }
        [[nodiscard]] constexpr auto fend(this auto&& self) noexcept { return &self.container_[self.index_]; }

        [[nodiscard]] constexpr const_iterator cbegin() const noexcept { return fbegin(); }
        [[nodiscard]] constexpr const_iterator cend() const noexcept { return fend(); }
        [[nodiscard]] constexpr const_iterator begin() const noexcept { return fbegin(); }
        [[nodiscard]] constexpr const_iterator end() const noexcept { return fend(); }

        //=========================================================================
		// Capacity
		//=========================================================================
        [[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }
        [[nodiscard]] constexpr std::size_t size() const noexcept { return index_; }
        [[nodiscard]] constexpr std::size_t max_size() const noexcept { return container_.max_size(); }

        //=========================================================================
		// Modifiers
		//=========================================================================
        constexpr void clear(std::optional<mapped_type> value = {}) noexcept
        {
            index_ = 0;
            if(value.has_value()) 
                initialValue_ = value.value();
        }

        //=========================================================================
		// Lookup
		//=========================================================================
        [[nodiscard]] constexpr auto find(this auto&& self, a_key_type key)
        {
            auto is_same = [&](auto&& arrayKey) { return arrayKey.first == key; };
			return std::ranges::find_if(self.fbegin(), self.fend(), is_same);
        }
        
        [[nodiscard]] constexpr bool contains(a_key_type key) const
        {
            return find(key) != fend();
        }

        [[nodiscard]] constexpr auto lower_bound(this auto&& self, a_key_type key)
        {
			auto is_not_less = [&](auto&& arrayKey) { return arrayKey.first >= key; };
			return std::ranges::find_if(self.fbegin(), self.fend(), is_not_less);
        }

        [[nodiscard]] constexpr auto upper_bound(this auto&& self, a_key_type key)
        {
            auto is_greater = [&](auto&& arrayKey) { return arrayKey.first > key; };
            return std::ranges::find_if(self.fbegin(), self.fend(), is_greater);
        }

    public:
        storage_type container_{};
        std::size_t index_{};
        mapped_type initialValue_{};
    };
}