#pragma once

// #define LINCPP_DEBUG

#define CHECK_FUNC(func, input, output)                                                                           \
    static_assert(std::is_invocable_v<func, input>, "function cannot be invoked with the specified input type."); \
    static_assert(std::is_same_v<typename std::result_of_t<func(input)>, output>, "function does not output the specified return type.");

#define CHECK_PREDICATE(pred, input) CHECK_FUNC(pred, input, bool)

/* #define CHECK_SOURCE_CONTENT(source, element, allowConversion)                                                                                                                                            \
    do                                                                                                                                                                                                    \
    {                                                                                                                                                                                                     \
        if constexpr (std::is_base_of_v<Queriable<source>, source>)                                                                                                                                       \
        {                                                                                                                                                                                                 \
            if constexpr (allowConversion)                                                                                                                                                               \
            {                                                                                                                                                                                             \
                static_assert(std::is_convertible_v<typename internal::traits<source>::Element, element>, "source does not have the specified element type as value type, nor it is convertible to it."); \
            }                                                                                                                                                                                             \
            else                                                                                                                                                                                          \
            {                                                                                                                                                                                             \
                static_assert(std::is_same_v<typename internal::traits<source>::Element, element>, "source does not have the specified element type as value type.");                                     \
            }                                                                                                                                                                                             \
        }                                                                                                                                                                                                 \
        else                                                                                                                                                                                              \
        {                                                                                                                                                                                                 \
            static_assert(std::is_same_v<typename source::value_type, element>, "source does not have the specified element type as value type.");                                                        \
        }                                                                                                                                                                                                 \
    } while (false)

#define CHECK_ITERATOR_TYPE(iterator, element) \
    static_assert(std::is_same_v<typename std::iterator_traits<iterator>::value_type, element>, "iterator does not point to the specified element type.");

#define CHECK_QUERIABLE_BASE(class) \
    static_assert(std::is_base_of_v<Queriable<class>, class>, "can only perform queries on Lincpp classes."); */
