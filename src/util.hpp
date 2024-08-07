#pragma once

namespace farra
{
    template<typename T>
    concept has_operator_less = requires(T type) { T{} < T{}; };

    template<std::size_t N, typename... Args>
    concept less_than = sizeof...(Args) <= N; 

    template<typename T>
    struct avoid_copy { using type = std::conditional_t<(sizeof(T) > 8), T&&, T>; };
    template<typename T>
    using avoid_copy_t = typename avoid_copy<T>::type;

    template<typename T>
    struct if_optional { using type = std::conditional_t<(std::is_trivially_default_constructible_v<T>), std::optional<T>, T>; };
    template<typename T>
    using if_optional_t = typename if_optional<T>::type;
}