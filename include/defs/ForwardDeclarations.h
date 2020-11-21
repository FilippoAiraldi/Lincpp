#pragma once

namespace Lincpp
{
    namespace internal
    {
        // structure whose specializations contains type infos on classes that provide one
        template <typename T>
        struct traits;
    } // namespace internal

    // template <typename T>
    // using lincpp_container = std::vector<T>; could use simple arrays inside Enumerable

    template <typename TIterator>
    struct Source;

    template <typename Derived>
    struct Queriable;

    template <typename Derived>
    struct QueriableIterator;

    // template <typename TElement>
    // struct Enumerable;

    // template <typename TElement, typename TSource, typename TReturn>
    // struct CastClause;

    // template <typename TElement, typename TSource, typename TFunc, typename TReturn>
    // struct SelectClause;
} // namespace Lincpp
