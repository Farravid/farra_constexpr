#pragma once

#include <memory>
#include <functional>
#include "util.hpp"

namespace farra
{
    template <typename T>
    struct function;

    template<typename Return_t, typename... Args>
    struct function<Return_t(Args...)>
    {
        constexpr function() noexcept = default;
        template<typename Callable_t>
        constexpr explicit function(Callable_t callable) noexcept
            : fn{ std::make_unique<impl<Callable_t>>(callable) }
        {}

        constexpr Return_t operator()(Args&&... args) const { return fn->call(args...); }

    private:
        struct interface
        {
            constexpr virtual Return_t call(const Args... args) const = 0;
            constexpr virtual ~interface() = default;
        };

        template <typename Callable_t>
        struct impl final : interface
        {
            constexpr explicit impl(Callable_t unique) : callable { unique } {}

            constexpr Return_t call(Args... args) const
            {
                if constexpr (std::is_member_function_pointer_v<Callable_t>)
                {
                    auto memfn = std::mem_fn(callable);
                    return memfn(args...);
                }
                else
                    return callable(args...);
                
                return Return_t{};
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

    template<typename Return_t, typename Class_t, typename... Args>
    struct function_traits<Return_t(Class_t::*) (Args...) const>
    {
        using type = Return_t(Args...);
    };

    template<typename Callable_t>
    function(Callable_t) 
    -> function<typename function_traits<decltype(&Callable_t::operator())>::type>;

    template<typename Return_t, typename... Args> 
    function(Return_t(Args...)) 
    -> function<Return_t(Args...)>;

    template<typename Return_t, typename Class_t, typename... Args> 
    function(Return_t (Class_t::*)(Args...)) 
    -> function<Return_t (Class_t&, Args...)>;

    template<typename Return_t, typename Class_t, typename... Args> 
    function(Return_t (Class_t::*)(Args...) const) 
    -> function<Return_t (const Class_t&, Args...)>;
}