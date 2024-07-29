namespace farra
{
    template<typename T>
    concept has_operator_less = requires(T type) { T{} < T{}; };

    template<typename T>
    struct avoid_copy { using type = std::conditional_t<(sizeof(T) > 8), T&, T>; };
    template<typename T>
    using avoid_copy_t = typename avoid_copy<T>::type;
}