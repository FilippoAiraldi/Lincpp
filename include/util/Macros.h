#pragma once

// invokable and functions
#define CHECK_FUNC(func, input, output)                                                                           \
    static_assert(std::is_invocable_v<func, input>, "function cannot be invoked with the specified input type."); \
    static_assert(std::is_same_v<typename std::result_of_t<func(input)>, output>, "function does not output the specified return type.");

#define CHECK_FUNC_WITH_ALLOWED_CONVERSION(func, input, output)                                                   \
    static_assert(std::is_invocable_v<func, input>, "function cannot be invoked with the specified input type."); \
    static_assert(std::is_convertible_v<typename std::result_of_t<func(input)>, output>, "function does not output the specified return type, nor it is convertible to.");

#define CHECK_PREDICATE(pred, input) CHECK_FUNC(pred, input, bool)

#define CHECK_COMPARER(func, input)                                                                                      \
    static_assert(std::is_invocable_v<func, input, input>, "comparer cannot be invoked with the specified input type."); \
    static_assert(std::is_same_v<typename std::result_of_t<func(input, input)>, bool>, "comparer does not output a boolean.");

// types
#define CHECK_INTEGRAL_OR_FLOATING(type) \
    static_assert(std::is_integral_v<type> || std::is_floating_point_v<type>, "type must be integral of floating.");
