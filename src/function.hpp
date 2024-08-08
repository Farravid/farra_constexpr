#pragma once

#include <memory>
#include "util.hpp"

namespace farra
{
    template <typename T>
    struct function;

    template<typename Return_t, typename... Args>
    struct function<Return_t(Args...)>
    {
        constexpr function() noexcept = default;
        template<std::invocable Callable_t>
        constexpr explicit function(Callable_t callable) noexcept
            : fn{ std::make_unique<impl<Callable_t>>(callable) }
        {}

        constexpr Return_t operator()(Args&&... args)
        {
            return fn->call(args...);
        }

    private:
        struct interface
        {
            constexpr virtual Return_t call(Args... args) = 0;
            constexpr virtual ~interface() = default;
        };

        template <typename Callable_t>
        struct impl : interface
        {
            constexpr explicit impl(Callable_t unique) : callable { unique } {}

            constexpr virtual Return_t call(Args... args) override final
            {
                return callable.operator()(args...);
            }

            Callable_t callable{};
        };


    private:
        std::unique_ptr<interface> fn{};
    };

    //=========================================================================
	// CTAD
	//=========================================================================
    template<typename Callable_t>
    struct function_traits {};

    template<typename Return_t, typename Class_t, typename ...Args>
    struct function_traits<Return_t(Class_t::*) (Args...) const>
    {
        using type = Return_t(Args...);
    };

    template<typename Callable_t>
    function(Callable_t) -> function<typename function_traits<decltype(&Callable_t::operator())>::type>;
}