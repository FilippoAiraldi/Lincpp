#pragma once

/* #define CHECK_CONTAINER_CONTENT(source, element) \
    static_assert(std::is_same_v<typename source::value_type, element>, "source does not have the given element type as value type.");

#define CHECK_ENUMERABLE_CONTENT(source, element) \
    static_assert(std::is_same_v<typename internal::traits<source>::Element, element>, "source does not have the given element type as value type."); */

#define CHECK_SOURCE_CONTENT(source, element)                                                                                                                 \
    do                                                                                                                                                        \
    {                                                                                                                                                         \
        if constexpr (std::is_base_of_v<Queriable<source>, source>)                                                                                           \
        {                                                                                                                                                     \
            static_assert(std::is_same_v<typename internal::traits<source>::Element, element>, "source does not have the given element type as value type."); \
        }                                                                                                                                                     \
        else                                                                                                                                                  \
        {                                                                                                                                                     \
            static_assert(std::is_same_v<typename source::value_type, element>, "source does not have the given element type as value type.");                \
        }                                                                                                                                                     \
    } while (false)

#define CHECK_LINCPP_QUERIABLE(class) \
    static_assert(std::is_base_of_v<Queriable<class>, class>, "can only perform queries on Lincpp classes.");

#define CHECK_FUNC(func, input, output)                                                                   \
    static_assert(std::is_invocable_v<func, input>, "function cannot be invoked with given input type."); \
    static_assert(std::is_same_v<typename std::result_of_t<func(const input &)>, output>, "function does not output the given return type.");

#define CHECK_PREDICATE(pred, input)                                                                       \
    static_assert(std::is_invocable_v<pred, input>, "predicate cannot be invoked with given input type."); \
    static_assert(std::is_same_v<typename std::result_of_t<pred(const input &)>, bool>, "predicate does not output bool as return type.");
